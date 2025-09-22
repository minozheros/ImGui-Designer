#pragma once

#include "core/interfaces/drawable.hpp"
#include <string>
#include <unordered_map>
#include <functional>
#include "core/interfaces/screen_base.hpp"

namespace core
{

    using ScreenActionMap = std::unordered_map<std::string, std::function<void(core::ScreenBase *)>>;
    using ScreenActionRegistry = std::unordered_map<std::string, ScreenActionMap>;

    // A base class for registry-driven drawables (screens)
    class DrawableBase : public Drawable
    {
    public:
        DrawableBase(ScreenActionRegistry *registry, std::string screenType, std::string actionName)
            : m_registry(registry), m_screenType(std::move(screenType)), m_actionName(std::move(actionName)), m_screenBase(nullptr) {}

        virtual ~DrawableBase() = default;

        // Set the ScreenBase pointer for the draw call
        void setScreenBase(core::ScreenBase *screen) { m_screenBase = screen; }

        bool draw() override
        {
            if (!m_registry || m_screenType.empty() || m_actionName.empty() || !m_screenBase)
                return false;
            auto typeIt = m_registry->find(m_screenType);
            if (typeIt != m_registry->end())
            {
                auto &actionMap = typeIt->second;
                auto actionIt = actionMap.find(m_actionName);
                if (actionIt != actionMap.end() && actionIt->second)
                {
                    try
                    {
                        actionIt->second(m_screenBase);
                        return true;
                    }
                    catch (const std::exception &)
                    {
                        // Optionally log error
                    }
                }
            }
            return false;
        }

        void setActionRegistry(ScreenActionRegistry *registry) { m_registry = registry; }
        void setScreenType(const std::string &type) { m_screenType = type; }
        void setActionName(const std::string &name) { m_actionName = name; }

    protected:
        ScreenActionRegistry *m_registry;
        std::string m_screenType;
        std::string m_actionName;
        core::ScreenBase *m_screenBase;
    };

} // namespace core
