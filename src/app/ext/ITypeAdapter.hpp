#pragma once

#include "ExtensibilityFwd.hpp"
#include "IReplaceable.hpp"
#include <string>
#include <memory>

namespace ImGuiDesigner
{

    class ITypeAdapter : public IReplaceable
    {
    public:
        ~ITypeAdapter() override = default;

        virtual const std::string &id() const = 0;         // Adapter id
        virtual const std::string &targetType() const = 0; // Qualified type name
        // Future: virtual void *createDefaultInstance() const = 0;
    };

} // namespace ImGuiDesigner
