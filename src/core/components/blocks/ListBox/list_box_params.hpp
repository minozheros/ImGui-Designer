#pragma once
#include <imgui.h>
#include <string>

struct ListBoxParams {
    std::string label;
    int* current_item;
    std::string const;
    int items_count;
    int height_in_items;
};
