/*================================================================
*  Copyright (C)2020 All rights reserved.
*  FileName : LifeWindow.cc
*  Author   : elonkou
*  Email    : elonkou@ktime.cc
*  Date     : Mon 01 Feb 2021 05:03:35 PM CST
================================================================*/

#include "LifeWindow.hh"

LifeWindow::LifeWindow() {
}

LifeWindow::~LifeWindow() {
}

void LifeWindow::Show() {
    if (!life) {
        return;
    }
    ImVec2 off;
    float  size = 8;
    float  padd = 2;

    if (ImGui::Begin("Life Display Window", &manager->options.show_map_window, 0)) {
        ImGui::BeginChild("Canvas", ImVec2(0, 0), 1, 0);
        ImVec2 p0;
        ImVec2 p1;
        auto   start_pos   = ImGui::GetCursorScreenPos();
        auto   drawList    = ImGui::GetWindowDrawList();
        ImVec2 window_size = ImGui::GetCurrentWindow()->Size;
        ImVec2 map_size    = ImVec2(life->width * (size + padd) - padd, life->height * (size + padd) - padd);
        ImVec2 offset      = ImVec2((window_size.x - map_size.x) / 2 + start_pos.x, (window_size.y - map_size.y) / 2 + start_pos.y);
        // ImVec2 end_pos     = ImVec2(start_pos.x + window_size.x, start_pos.y + window_size.y);

        for (int i = 0; i < life->height; i++) {
            for (int j = 0; j < life->width; j++) {
                p0 = {offset.x + (size + padd) * j, offset.y + (size + padd) * i};
                p1 = p0 + ImVec2(size, size);
                if (life->map[i][j] == 1) {
                    // map[i][j] == 1
                    ImVec4 color = ImVec4(0.6, 0.6, 0.6, 1.0);
                    drawList->AddRectFilled(p0, p1, ImGui::ColorConvertFloat4ToU32(color));
                } else {
                    // map[i][j] == 0
                    ImVec4 color = ImVec4(0.03, 0.03, 0.03, 1.0);
                    drawList->AddRectFilled(p0, p1, ImGui::ColorConvertFloat4ToU32(color));
                }
            }
        }
        ImGui::EndChild();
    }
    ImGui::End();
}
