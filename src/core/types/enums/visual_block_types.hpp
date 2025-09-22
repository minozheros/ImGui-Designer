#pragma once

// Enum for all supported block types
// Will be generated/updated automatically by the block generation script.
// Don't edit it manually.

enum class VisualBlockType
{
    ImGui_Checkbox,
    ImGui_Button,
    ImGui_InputText,
    ImGui_InputFloat,
    ImGui_InputInt,
    ImGui_Combo,
    ImGui_SliderFloat,
    ImGui_SliderInt,
    ImGui_Selectable,
    ImGui_ColorEdit3,
    ImGui_ColorEdit4,
    ImGui_ProgressBar,
    ImGui_Text,
    ImGui_ImageButton,
    ImPlot_PlotLine,
    Vector2ValueBlock,
    Vector3ValueBlock,
    Vector4ValueBlock,
    FilePathValueBlock,
    RangeValueBlock,
    DateTimeValueBlock,
    TextAreaValueBlock,
    EnumValueBlock,
    MultiSelectEnumBlock,
    ImageBlock,
    EventDispatchBlock,
    EventReceiveBlock,
    ImGuiWindowBlock,
    FlagOptionSelectorBlock,

    // Add new block types above this line
    COUNT // Keep this as the last entry to track the number of block types
};