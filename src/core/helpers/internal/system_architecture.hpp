#pragma once
#include "internal/system_architecture.hpp"
namespace core
{

        // Detects and returns the current CPU architecture
        inline SystemArchitecture getArchitecture()
        {
#if defined(__x86_64__) || defined(_M_X64)
                return SystemArchitecture::X86_64;
#elif defined(__i386) || defined(_M_IX86)
                return SystemArchitecture::X86;
#elif defined(__aarch64__)
                return SystemArchitecture::ARM64;
#elif defined(__arm__)
                return SystemArchitecture::ARM;
#else
                return SystemArchitecture::Unknown;
#endif
        }
}