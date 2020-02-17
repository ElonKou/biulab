#pragma once
#ifndef IMGUI_BIULAB_WIDGETS_H_
#define IMGUI_BIULAB_WIDGETS_H_

#include "imgui.h"
#include <cstdint>
#include <iostream>
#include <string>
#ifndef IMGUI_DEFINE_MATH_OPERATORS
#define IMGUI_DEFINE_MATH_OPERATORS
#endif
#include "imgui_internal.h"

using namespace std;

namespace ImGui {

IMGUI_API bool SmallRadioButton(const char* label, bool active);
IMGUI_API bool SmallRadioButton(const char* label, int* v, int v_button);
IMGUI_API bool ColorRadioButton(const char* label, bool active, ImVec4 color);
IMGUI_API bool ColorRadioButton(const char* label, int* v, int v_button, ImVec4 color);

IMGUI_API bool ThumbNail(ImTextureID user_texture_id, const ImVec2& size, std::string label, const ImVec2ih& uv, const size_t& index);

IMGUI_API void DrawRobbie(ImDrawList* draw_list, ImVec2& p0, ImVec2& p1, ImVec4& color);

} // namespace ImGui

#endif