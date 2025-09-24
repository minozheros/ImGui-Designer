#pragma once
#include "IExampleInterface.hpp"
#include <string>

/**
 * @brief Concrete implementation of IExampleInterface
 *
 * This example shows how to implement an interface that uses
 * co-located enums. Notice how the enums are available without
 * additional includes.
 */

namespace example
{

    /**
     * @brief Example implementation demonstrating the interface pattern
     */
    class ExampleComponent : public IExampleInterface
    {
    public:
        ExampleComponent() = default;
        ~ExampleComponent() override = default;

        // Implementation of interface methods
        void setState(ExampleState state) override
        {
            currentState = state;
            // Handle state transitions
            switch (state)
            {
            case ExampleState::Active:
                // Activation logic
                break;
            case ExampleState::Inactive:
                // Deactivation logic
                break;
            case ExampleState::Error:
                // Error handling
                break;
            }
        }

        ExampleState getState() const override
        {
            return currentState;
        }

        void setMode(ExampleMode mode) override
        {
            currentMode = mode;
        }

        ExampleMode getMode() const override
        {
            return currentMode;
        }

        void process() override
        {
            if (currentState == ExampleState::Active)
            {
                // Processing logic based on mode
                switch (currentMode)
                {
                case ExampleMode::Automatic:
                    // Auto processing
                    break;
                case ExampleMode::Manual:
                    // Manual processing
                    break;
                case ExampleMode::Debug:
                    // Debug processing with logging
                    break;
                }
            }
        }

        bool isReady() const override
        {
            return currentState != ExampleState::Error;
        }

    private:
        ExampleState currentState = ExampleState::Inactive;
        ExampleMode currentMode = ExampleMode::Automatic;
    };

} // namespace example