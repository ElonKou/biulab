/*================================================================
*  Copyright (C)2019 All rights reserved.
*  FileName : OverviewWindow.cc
*  Author   : elonkou
*  Email    : elonkou@ktime.cc
*  Date     : 2019年12月22日 星期日 10时43分41秒
================================================================*/

#include "OverviewWindow.hh"
#include "DynamicClass.hh"
#include <iostream>

using namespace std;

DYN_DECLARE(OverviewWindow);

OverviewWindow::OverviewWindow() {}

OverviewWindow::~OverviewWindow() {}

void OverviewWindow::Show() {
    ImGui::SetNextWindowBgAlpha(0.3f);
    if (ImGui::Begin("Overlay", &show_overlay_bar, 0)) {
        ImGui::Text("C : Open control panel.");
        ImGui::Text("D : Open display panel.");
        // ImGui::Separator();
        ImGui::Text("F : %.1f.", ImGui::GetIO().Framerate);
        if (ImGui::IsMousePosValid()) {
            ImGui::SameLine();
            ImGui::Text("(%6.1f,%6.1f)", ImGui::GetIO().MousePos.x,
                        ImGui::GetIO().MousePos.y);
        } else {
            ImGui::SameLine();
            ImGui::Text("<invalid>");
        }
        if (info) {
            for (auto iter = info->items.begin(); iter != info->items.end(); iter++) {
                for (auto it = iter->second.data.begin(); it != iter->second.data.end(); it++) {
                    string name = it->first + ": " + it->second;
                    ImGui::Text("%s", name.c_str());
                }
            }
        }
    }
    ImGui::End();
}

void OverviewWindow::UpdateData() {
    info = GetData<OverviewInfo>("OverviewInfo");
}