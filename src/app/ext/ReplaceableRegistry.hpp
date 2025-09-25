#pragma once

#include <unordered_map>
#include <memory>
#include <string>
#include <mutex>
#include <optional>

namespace ImGuiDesigner
{

    // Simple non-thread-safe (currently) registry for replaceable components.
    // Future layering: Session > User > Pack > Descriptor > Core.
    // For now we just store by id within a single map.

    template <typename IFace>
    class ReplaceableRegistry
    {
    public:
        using Ptr = std::shared_ptr<IFace>;

        bool registerItem(const std::string &id, Ptr item)
        {
            if (!item)
                return false;
            auto [it, inserted] = items.emplace(id, std::move(item));
            if (!inserted)
            {
                // Overwrite existing intentionally (could track provenance later)
                it->second = std::move(item);
                return true;
            }
            return inserted;
        }

        Ptr get(const std::string &id) const
        {
            auto it = items.find(id);
            if (it == items.end())
                return nullptr;
            return it->second;
        }

        bool remove(const std::string &id)
        {
            return items.erase(id) > 0;
        }

        void clear() { items.clear(); }

        std::size_t size() const { return items.size(); }

    private:
        std::unordered_map<std::string, Ptr> items;
    };

} // namespace ImGuiDesigner
