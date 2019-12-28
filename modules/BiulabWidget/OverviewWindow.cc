/*================================================================
*  Copyright (C)2019 All rights reserved.
*  FileName : OverviewWindow.cc
*  Author   : elonkou
*  Email    : elonkou@ktime.cc
*  Date     : 2019年12月22日 星期日 10时43分41秒
================================================================*/

#include "OverviewWindow.hh"
#include <iostream>
#include "DynamicClass.hh"

using namespace std;

DYN_DECLARE(OverviewWindow);

OverviewWindow::OverviewWindow() {}

OverviewWindow::~OverviewWindow() {}

void OverviewWindow::show() {
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
            ImGui::Text("<invalid>");
        }
        // ImGui::Text("Slection");
        // ImGui::Text("robbie:%s", ins_select_robbie.c_str());
        // ImGui::Text("map:%s", ins_select_map.c_str());
    }
    ImGui::End();
}