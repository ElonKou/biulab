/*================================================================
*  Copyright (C)2020 All rights reserved.
*  FileName : imgui_biulab_widgets.cpp
*  Author   : elonkou
*  Email    : elonkou@ktime.cc
*  Date     : 2020年02月08日 星期六 00时17分21秒
================================================================*/

#include "imgui_biulab_widgets.h"

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

bool ImGui::ThumbNail(ImTextureID user_texture_id, const ImVec2& size, std::string label, const ImVec2ih& uv, const size_t& index) {
    int           frame_padding = -1;
    int           offset        = 16;
    const ImVec4& bg_col        = ImVec4(0, 0, 0, 0);
    const ImVec4& tint_col      = ImVec4(1, 1, 1, 1);
    bool          one_line      = false;
    ImVec2ih      idx           = ImVec2ih(index % uv.y, index / uv.y);

    ImGuiWindow* window = GetCurrentWindow();
    if (window->SkipItems)
        return false;

    ImGuiContext&     g     = *GImGui;
    const ImGuiStyle& style = g.Style;

    // Default to using texture ID as ID. User can still push string/integer prefixes.
    // We could hash the size/uv to create a unique ID but that would prevent the user from animating UV.
    PushID((void*)(intptr_t)user_texture_id);
    const ImGuiID id = window->GetID("#image");
    PopID();

    const ImVec2 label_size  = CalcTextSize(label.c_str(), NULL, true);
    const ImVec2 label_fill  = ImVec2(0, label_size.y);
    const ImVec2 padding     = (frame_padding >= 0) ? ImVec2((float)frame_padding, (float)frame_padding) : style.FramePadding;
    const ImVec2 window_size = ImGui::GetCurrentWindow()->Size;
    ImVec2       bbox        = size + label_fill + padding * 2;
    ImVec2       start_pos   = ImVec2((window_size.x - uv.y * size.x - (uv.y - 1) * offset) / 2.0 + bbox.x * idx.x, (window_size.y - uv.x * size.y - (uv.x - 1) * offset) / 2.0 + bbox.y * idx.y);
    ImVec2       margin      = ImVec2(idx.x * offset, idx.y * offset);
    const ImRect bb(start_pos + margin, start_pos + size + label_fill + padding * 2 + margin);
    const ImRect image_bb(start_pos + padding + margin, start_pos + padding + size + margin);
    const ImVec2 label_pos = ImVec2(start_pos.x + padding.x + (bb.Max.x - bb.Min.x - label_size.x) / 2.0 + margin.x, start_pos.y + size.y + padding.y + margin.y);
    ItemSize(bb);
    if (!ItemAdd(bb, id))
        return false;

    bool hovered, held;
    bool pressed = ButtonBehavior(bb, id, &hovered, &held);

    // Render
    const ImU32 col = GetColorU32((held && hovered) ? ImGuiCol_ButtonActive : hovered ? ImGuiCol_ButtonHovered : ImGuiCol_Button);
    RenderNavHighlight(bb, id);
    RenderFrame(bb.Min, bb.Max, col, true, ImClamp((float)ImMin(padding.x, padding.y), 0.0f, style.FrameRounding));
    if (bg_col.w > 0.0f)
        window->DrawList->AddRectFilled(image_bb.Min, image_bb.Max, GetColorU32(bg_col));
    window->DrawList->AddImage(user_texture_id, image_bb.Min, image_bb.Max, ImVec2(0, 0), ImVec2(1, 1), GetColorU32(tint_col));
    window->DrawList->AddText(label_pos, GetColorU32(tint_col), label.c_str());

    return pressed;
}
