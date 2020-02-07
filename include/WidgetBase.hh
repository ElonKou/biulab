#pragma once
#ifndef WIDGHT_BASE_H_
#define WIDGHT_BASE_H_

#include "Base.hh"
#include <string>

using namespace std;

class WidgetBase : public Base {
  public:
    WidgetBase() {}

    ~WidgetBase() {}

    virtual void Show() = 0;

    void showHelpMarker(const string dsec) {
        ImGui::TextDisabled("(?)");
        if (ImGui::IsItemHovered()) {
            ImGui::BeginTooltip();
            ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
            ImGui::TextUnformatted(dsec.c_str());
            ImGui::PopTextWrapPos();
            ImGui::EndTooltip();
        }
    }
};

#endif