/*================================================================
*  Copyright (C)2019 All rights reserved.
*  FileName : core/Widget.cc
*  Author   : elonkou
*  Email    : elonkou@ktime.cc
*  Date     : 2019年11月11日 星期一 23时22分46秒
================================================================*/

#include "Widget.hh"

namespace BiuLab {
namespace Widget {

Widget::Widget() {}

Widget::~Widget() {}

void Widget::showHelpMarker(const string desc) {
    ImGui::TextDisabled("(?)");
    if (ImGui::IsItemHovered()) {
        ImGui::BeginTooltip();
        ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
        ImGui::TextUnformatted(desc.c_str());
        ImGui::PopTextWrapPos();
        ImGui::EndTooltip();
    }
}

}  // namespace Widget

}  // namespace BiuLab
