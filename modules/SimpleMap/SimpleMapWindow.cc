/*================================================================
*  Copyright (C)2019 All rights reserved.
*  FileName : SimpleMapWindow.cc
*  Author   : elonkou
*  Email    : elonkou@ktime.cc
*  Date     : 2019年12月29日 星期日 13时21分39秒
================================================================*/

#include "SimpleMapWindow.hh"
#include "DynamicClass.hh"
#include <string>

using namespace std;

DYN_DECLARE(SimpleMapWindow);

SimpleMapWindow::SimpleMapWindow() {
    bsize      = 16.0f;
    padding    = 1.0f;
    simple_map = nullptr;
}

SimpleMapWindow::~SimpleMapWindow() {}

void SimpleMapWindow::UpdateData() {
    simple_map = GetData<SimpleMap>("SimpleMap");
    map_editor = GetData<MapEditor>("MapEditor");
}

void SimpleMapWindow::Show() {
    if (!simple_map) {
        return;
    }
    if (ImGui::Begin("Simple Map", &show_simplemap_window, 0)) {
        ImGui::BeginChild("Canvas", ImVec2(0, 0), 1, 0);
        auto   start_pos   = ImGui::GetCursorScreenPos();
        auto   drawList    = ImGui::GetWindowDrawList();
        ImVec2 window_size = ImGui::GetCurrentWindow()->Size;
        ImVec2 offset;
        ImVec2 map_size = ImVec2(simple_map->size.x * bsize, simple_map->size.y * bsize);
        ImVec2 end_pos  = ImVec2(start_pos.x + window_size.x, start_pos.y + window_size.y);
        offset.x        = (window_size.x - map_size.x) / 2 + start_pos.x;
        offset.y        = (window_size.y - map_size.y) / 2 + start_pos.y;

        for (int i = 0; i < simple_map->size.y; i++) {
            for (int j = 0; j < simple_map->size.x; j++) {
                ImVec2 p0 = {offset.x + j * bsize, offset.y + i * bsize};
                ImVec2 p1 = {offset.x + (j + 1) * bsize - padding,
                             offset.y + (i + 1) * bsize - padding};
                if (simple_map->map[i][j] == MAP_EDGE) {
                    drawList->AddRectFilled(p0, p1, ImGui::ColorConvertFloat4ToU32(simple_map->infos["MAP_EDGE"].color));
                } else if (simple_map->map[i][j] == MAP_RUBBISH) {
                    drawList->AddRectFilled(p0, p1, ImGui::ColorConvertFloat4ToU32(simple_map->infos["MAP_RUBBISH"].color));
                } else if (simple_map->map[i][j] == MAP_EMPTY) {
                    drawList->AddRectFilled(p0, p1, ImGui::ColorConvertFloat4ToU32(simple_map->infos["MAP_EMPTY"].color));
                } else if (simple_map->map[i][j] == MAP_OUT) {
                    drawList->AddRectFilled(p0, p1, ImGui::ColorConvertFloat4ToU32(simple_map->infos["MAP_OUT"].color));
                }
                // Hover
                if (ImGui::IsMouseHoveringRect(p0, p1)) {
                    if (ImGui::IsMouseClicked(0)) {
                        map_editor->ModifiedMap(*simple_map, vec_2i(j, i));
                    }
                }
            }
        }
        if (ImGui::IsMouseHoveringRect(start_pos, end_pos)) {
            ImGuiIO& io = ImGui::GetIO();
            if (io.MouseWheel != 0.0) {
                bsize += io.MouseWheel;
                bsize = MAX(bsize, 4);
                bsize = MIN(bsize, 64);
            }
        }
        ImGui::EndChild();
    }
    ImGui::End();
}