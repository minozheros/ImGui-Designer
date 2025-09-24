# Interface Design Patterns

This directory contains examples and templates demonstrating best practices for interface design in the ImGui-Designer project.

## Co-located Enums Pattern

### Overview

Interface-specific enums should be defined within the same header file as the interface they belong to. This pattern improves code cohesion and reduces include complexity.

### When to Use

- ✅ **Use co-located enums** for enums that are specific to an interface's contract
- ✅ **Use co-located enums** when the enum values are tightly coupled to interface behavior
- ❌ **Don't use co-located enums** for global enums used across multiple subsystems
- ❌ **Don't use co-located enums** for enums that need to be shared between unrelated interfaces

### Examples

#### Good: Interface-Specific Enum

```cpp
// IVisible.hpp - VisibilityState is only used by visibility interfaces
enum class VisibilityState { Visible, Hidden, Collapsed };

struct IVisible {
    virtual void setVisible(VisibilityState state) = 0;
    // ...
};
```

#### Bad: Global Enum in Interface File

```cpp
// Don't put ParameterType here - it's used by many components
enum class ParameterType { Input, Output, Return }; // ❌ Wrong location

struct IParameter {
    virtual ParameterType getType() const = 0; // ❌
};
```

### Global Enums Location

Global enums that are used across multiple subsystems should be placed in:

```text
src/core/types/enums/
```

### Benefits

1. **Reduced includes** - No need for separate enum header includes
2. **Better cohesion** - Related types are grouped together
3. **Clearer ownership** - Enum belongs to the interface that defines its behavior
4. **Easier maintenance** - Interface and enum changes happen in one place

### Files in This Directory

- `IExampleInterface.hpp` - Template showing the co-located enum pattern
- `ExampleComponent.hpp` - Concrete implementation example

### Usage

1. Copy `IExampleInterface.hpp` as a template for new interfaces
2. Define interface-specific enums within the interface header
3. Implement concrete classes that use the interface
4. Place global enums in `src/core/types/enums/` instead

### See Also

- `src/core/types/interfaces/IVisible.hpp` - Real example in the codebase
- `src/core/types/enums/ParameterType.hpp` - Example of properly placed global enum
