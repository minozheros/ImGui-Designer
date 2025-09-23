#pragma once
#include <imgui.h>
#include <string>

struct ComboParams {
    std::string label;
    int* current_item;
    std::string items_separated_by_zeros;
    int popup_max_height_in_items;
};
