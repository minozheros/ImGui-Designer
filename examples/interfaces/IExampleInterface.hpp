#pragma once

/**
 * @brief Template for interface definitions with co-located enums
 *
 * Pattern: Define interface-specific enums within the same header file
 * as the interface they belong to. This improves cohesion and reduces
 * include complexity.
 *
 * Usage:
 * - Copy this template for new interfaces
 * - Define enums specific to this interface's contract
 * - Keep global enums in src/core/types/enums/
 */

namespace example
{

    // Interface-specific enums belong here
    enum class ExampleState
    {
        Inactive,
        Active,
        Error
    };

    enum class ExampleMode
    {
        Automatic,
        Manual,
        Debug
    };

    /**
     * @brief Example interface demonstrating co-located enum pattern
     *
     * This interface shows how to structure interfaces with their
     * associated enums for maximum clarity and maintainability.
     */
    struct IExampleInterface
    {
        virtual ~IExampleInterface() = default;

        // State management
        virtual void setState(ExampleState state) = 0;
        virtual ExampleState getState() const = 0;

        // Mode configuration
        virtual void setMode(ExampleMode mode) = 0;
        virtual ExampleMode getMode() const = 0;

        // Core functionality
        virtual void process() = 0;
        virtual bool isReady() const = 0;
    };

} // namespace example