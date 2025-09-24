#pragma once
#include <string>
#include <any>

class IParameter
{
public:
    virtual ~IParameter() = default;
    virtual void render() = 0;                        // Render the UI for editing (e.g., ImGui::SliderFloat)
    virtual std::any getValue() const = 0;            // Get the value as any (for generic access)
    virtual void setValue(const std::any &value) = 0; // Set the value
    virtual std::string getName() const = 0;          // Parameter name (e.g., "width")
    virtual std::string getType() const = 0;          // Type string (e.g., "float")
    // Add methods for pointers/refs if needed, e.g.:
    virtual void *getValuePtr() = 0; // For ImGui calls needing pointers
    virtual std::any &getValueRef() = 0; // For ImGui calls needing references
};