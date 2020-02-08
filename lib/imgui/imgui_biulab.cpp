/*================================================================
*  Copyright (C)2020 All rights reserved.
*  FileName : imgui_biulab.cpp
*  Author   : elonkou
*  Email    : elonkou@ktime.cc
*  Date     : 2020年02月08日 星期六 00时17分21秒
================================================================*/

#include "imgui_biulab.h"

bool ImGui::SmallRadioButton(const char* label, bool active) {
    ImGuiWindow* window = GetCurrentWindow();
    if (window->SkipItems)
        return false;

    ImGuiContext&     g          = *GImGui;
    const ImGuiStyle& style      = g.Style;
    const ImGuiID     id         = window->GetID(label);
    const ImVec2      label_size = CalcTextSize(label, NULL, true);

    const float  square_sz = GetFrameHeight();
    const ImVec2 pos       = window->DC.CursorPos;
    const ImRect check_bb(pos, pos + ImVec2(square_sz, square_sz));
    const ImRect total_bb(pos, pos + ImVec2(square_sz + (label_size.x > 0.0f ? style.ItemInnerSpacing.x + label_size.x : 0.0f), label_size.y + style.FramePadding.y * 2.0f));
    ItemSize(total_bb, style.FramePadding.y);
    if (!ItemAdd(total_bb, id))
        return false;

    ImVec2 center      = check_bb.GetCenter();
    center.x           = (float)(int)center.x + 0.5f;
    center.y           = (float)(int)center.y + 0.5f;
    const float radius = (square_sz - 6.0f) * 0.5f;

    bool hovered, held;
    bool pressed = ButtonBehavior(total_bb, id, &hovered, &held);
    if (pressed)
        MarkItemEdited(id);

    RenderNavHighlight(total_bb, id);
    window->DrawList->AddCircleFilled(center, radius, GetColorU32((held && hovered) ? ImGuiCol_FrameBgActive : hovered ? ImGuiCol_FrameBgHovered : ImGuiCol_FrameBg), 16);
    if (active) {
        const float pad = ImMax(1.0f, (float)(int)(square_sz / 6.0f));
        window->DrawList->AddCircleFilled(center, radius - pad, GetColorU32(ImGuiCol_CheckMark), 16);
    }

    if (style.FrameBorderSize > 0.0f) {
        window->DrawList->AddCircle(center + ImVec2(1, 1), radius, GetColorU32(ImGuiCol_BorderShadow), 16, style.FrameBorderSize);
        window->DrawList->AddCircle(center, radius, GetColorU32(ImGuiCol_Border), 16, style.FrameBorderSize);
    }

    if (g.LogEnabled)
        LogRenderedText(&total_bb.Min, active ? "(x)" : "( )");
    if (label_size.x > 0.0f)
        RenderText(ImVec2(check_bb.Max.x + style.ItemInnerSpacing.x, check_bb.Min.y + style.FramePadding.y), label);

    return pressed;
}

bool ImGui::SmallRadioButton(const char* label, int* v, int v_button) {
    const bool pressed = SmallRadioButton(label, *v == v_button);
    if (pressed)
        *v = v_button;
    return pressed;
}

bool ImGui::ColorRadioButton(const char* label, bool active, ImVec4 color) {
    ImGuiWindow* window = GetCurrentWindow();
    if (window->SkipItems)
        return false;

    ImGuiContext&     g            = *GImGui;
    const ImGuiStyle& style        = g.Style;
    const ImGuiID     id           = window->GetID(label);
    const float       square_sz    = GetFrameHeight();
    const float       offset       = 4;
    const float       width        = 2;
    const float       inner_offset = offset - width / 2;
    const ImVec2      label_size   = CalcTextSize(label, NULL, true);
    const ImVec2      start        = window->DC.CursorPos;
    const ImVec2      end          = start + ImVec2(square_sz, square_sz);
    const ImRect      check_bb(start, end);
    const ImRect      total_bb(start, start + ImVec2(square_sz + (label_size.x > 0.0f ? style.ItemInnerSpacing.x + label_size.x : 0.0f), label_size.y + style.FramePadding.y * 2.0f));
    ItemSize(total_bb, style.FramePadding.y);
    if (!ItemAdd(total_bb, id))
        return false;

    bool hovered, held;
    bool pressed = ButtonBehavior(total_bb, id, &hovered, &held);
    if (pressed)
        MarkItemEdited(id);

    RenderNavHighlight(check_bb, id);
    window->DrawList->AddRectFilled(start + ImVec2(offset, offset), end + ImVec2(-offset, -offset), GetColorU32(color));
    if (active) {
        ImVec2 p1 = start + ImVec2(inner_offset, inner_offset);
        ImVec2 p2 = start + ImVec2(square_sz - inner_offset, inner_offset);
        ImVec2 p3 = end + ImVec2(-inner_offset, -inner_offset);
        ImVec2 p4 = end + ImVec2(-square_sz + inner_offset, -inner_offset);
        window->DrawList->AddQuad(p1, p2, p3, p4, GetColorU32((held && hovered) ? ImGuiCol_FrameBgActive : hovered ? ImGuiCol_FrameBgHovered : ImGuiCol_FrameBg), width);
    }
    if (g.LogEnabled)
        LogRenderedText(&total_bb.Min, active ? "(x)" : "( )");
    if (label_size.x > 0.0f)
        RenderText(ImVec2(check_bb.Max.x + style.ItemInnerSpacing.x, check_bb.Min.y + style.FramePadding.y), label);
    return pressed;
}

bool ImGui::ColorRadioButton(const char* label, int* v, int v_button, ImVec4 color) {
    const bool pressed = ColorRadioButton(label, *v == v_button, color);
    if (pressed)
        *v = v_button;
    return pressed;
}