#!/bin/bash
set -e  # Exit on any error

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Function to run make with optional logging
run_make() {
    if [ "$LOG_OUTPUT" = true ]; then
        "$@" 2>&1 | tee build.log
        return ${PIPESTATUS[0]}
    else
        "$@"
    fi
}

# Function to print colored output
print_status() {
    echo -e "${BLUE}[BUILD]${NC} $1"
}

print_success() {
    echo -e "${GREEN}[SUCCESS]${NC} $1"
}

print_warning() {
    echo -e "${YELLOW}[WARNING]${NC} $1"
}

print_error() {
    echo -e "${RED}[ERROR]${NC} $1"
}

# Check if we're in the source directory
if [ ! -f "CMakeLists.txt" ]; then
    print_error "CMakeLists.txt not found. Please run this script from the project root directory."
    exit 1
fi

# Parse command line arguments
CLEAN_BUILD=false
BUILD_TYPE="Debug"
JOBS=$(nproc)
TARGET=""
RECONFIGURE=false
LOG_OUTPUT=false
AUTO_RECONFIGURE=false

while [[ $# -gt 0 ]]; do
    case $1 in
        clean)
            CLEAN_BUILD=true
            shift
            ;;
        reconfigure)
            RECONFIGURE=true
            shift
            ;;
        release)
            BUILD_TYPE="Release"
            shift
            ;;
        debug)
            BUILD_TYPE="Debug"
            shift
            ;;
        regenerate)
            TARGET="regenerate_all"
            shift
            ;;
        clean-generated)
            TARGET="clean_generated"
            shift
            ;;
        -j|--jobs)
            JOBS="$2"
            shift
            shift
            ;;
        --log)
            LOG_OUTPUT=true
            shift
            ;;
        -h|--help)
            echo "Usage: $0 [options]"
            echo ""
            echo "Options:"
            echo "  clean           Clean build directory before building"
            echo "  reconfigure     Reconfigure with CMake before building"
            echo "  release         Build in Release mode (default: Debug)"
            echo "  debug           Build in Debug mode (default)"
            echo "  regenerate      Regenerate all auto-generated files"
            echo "  clean-generated Clean all auto-generated files"
            echo "  -j N            Number of parallel jobs (default: $(nproc))"
            echo "  --log           Save build output to build/build.log"
            echo "  -h              Show this help"
            echo ""
            echo "Examples:"
            echo "  $0                    # Debug build"
            echo "  $0 reconfigure        # Reconfigure and build"
            echo "  $0 clean reconfigure  # Clean, reconfigure and build"
            echo "  $0 regenerate         # Regenerate all generated files"
            echo "  $0 --log              # Build and save output to build.log"
            exit 0
            ;;
        *)
            print_error "Unknown option: $1"
            echo "Use '$0 --help' for usage information."
            exit 1
            ;;
    esac
done

# Clean build if requested
if [ "$CLEAN_BUILD" = true ]; then
    print_status "Cleaning build directory..."
    rm -rf build
    print_success "Build directory cleaned."
fi

# Detect test file changes (only if tests are enabled by default; we always configure with tests ON later)
# This allows new/removed tests/test_*.cpp files to trigger an automatic reconfigure without the user
# needing to pass the 'reconfigure' argument manually.
TEST_MANIFEST_PATH="build/.tests_manifest"
if [ -d "tests" ]; then
    CURRENT_TEST_LIST=$(find tests -type f -name 'test_*.cpp' 2>/dev/null | sort)
    # Build a hash representing the set of test files plus their mtimes & sizes for robustness
    TEST_SIG=""
    while IFS= read -r f; do
        if [ -f "$f" ]; then
            stat_line=$(stat -c '%n:%Y:%s' "$f" 2>/dev/null || echo "$f:0:0")
            TEST_SIG+="$stat_line\n"
        fi
    done <<< "$CURRENT_TEST_LIST"
    TEST_HASH=$(printf "%s" "$TEST_SIG" | md5sum | cut -d' ' -f1)
    if [ -f "$TEST_MANIFEST_PATH" ]; then
        OLD_HASH=$(cut -d' ' -f1 "$TEST_MANIFEST_PATH" 2>/dev/null || true)
        if [ "$OLD_HASH" != "$TEST_HASH" ]; then
            AUTO_RECONFIGURE=true
        fi
    else
        # No manifest yet; trigger initial record after first configure
        AUTO_RECONFIGURE=true
    fi
fi

if [ "$AUTO_RECONFIGURE" = true ] && [ "$RECONFIGURE" = false ]; then
    print_status "Detected test file additions/removals/changes -> auto reconfigure will run."
    RECONFIGURE=true
fi

# Handle special targets that don't require full build setup
if [ -n "$TARGET" ]; then
    if [ ! -d "build" ]; then
        print_error "Build directory not found. Run '$0' first to set up the build."
        exit 1
    fi
    cd build
    print_status "Running target: $TARGET"
    if ! run_make make "$TARGET"; then
        print_error "Target '$TARGET' failed."
        exit 1
    fi
    print_success "Target '$TARGET' completed successfully!"
    exit 0
fi

# Create build directory if it doesn't exist
if [ ! -d "build" ]; then
    print_status "Creating build directory..."
    mkdir -p build
fi

cd build

# Configure with CMake (always if reconfigure is requested, or if CMakeCache.txt doesn't exist)
if [ "$RECONFIGURE" = true ] || [ ! -f "CMakeCache.txt" ]; then
    print_status "Configuring with CMake (Build Type: $BUILD_TYPE)..."
    if ! cmake -DCMAKE_BUILD_TYPE="$BUILD_TYPE" -DIMGUIDESIGNER_ENABLE_TESTS=ON ..; then
        print_error "CMake configuration failed."
        exit 1
    fi
elif [ "$CLEAN_BUILD" = true ]; then
    print_status "Reconfiguring after clean (Build Type: $BUILD_TYPE)..."
    if ! cmake -DCMAKE_BUILD_TYPE="$BUILD_TYPE" -DIMGUIDESIGNER_ENABLE_TESTS=ON ..; then
        print_error "CMake configuration failed."
        exit 1
    fi
else
    print_status "Using existing CMake configuration..."
fi

# Build
print_status "Building with $JOBS parallel jobs..."
if ! run_make make -j"$JOBS" ImGui-Designer ImGui-Designer_tests; then
    print_error "Build failed."
    exit 1
fi

print_success "Build completed successfully!"
print_status "You can now run: ./bin/ImGui-Designer"

# Persist new test manifest hash (after successful build) if we computed one
if [ -n "$TEST_HASH" ]; then
    printf "%s  tests\n" "$TEST_HASH" > "$TEST_MANIFEST_PATH" 2>/dev/null || true
fi