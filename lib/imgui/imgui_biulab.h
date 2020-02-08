#pragma once
#ifndef IMGUI_BIULAB_H_
#define IMGUI_BIULAB_H_

#include "imgui.h"
#ifndef IMGUI_DEFINE_MATH_OPERATORS
#define IMGUI_DEFINE_MATH_OPERATORS
#endif
#include "imgui_internal.h"

namespace ImGui {
IMGUI_API bool SmallRadioButton(const char* label, bool active);
IMGUI_API bool SmallRadioButton(const char* label, int* v, int v_button);
IMGUI_API bool ColorRadioButton(const char* label, bool active, ImVec4 color);
IMGUI_API bool ColorRadioButton(const char* label, int* v, int v_button, ImVec4 color);
} // namespace ImGui

#endif