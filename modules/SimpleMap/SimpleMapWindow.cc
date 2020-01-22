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
    has_map = false;
    map     = nullptr;
}

SimpleMapWindow::~SimpleMapWindow() {}

void SimpleMapWindow::SetCores(MapEditor* map_editor_, SimpleMap* simple_map_) {
    map        = simple_map_;
    has_map    = true;
    map_editor = map_editor_;
}

void SimpleMapWindow::ClearCores() {
    map     = nullptr;
    has_map = false;
}

void SimpleMapWindow::show() {
    if (!has_map || !map) {
        return;
    }
    if (ImGui::Begin("Simple Map", &show_simplemap_window, 0)) {
        static float bsize     = 16.0f;
        static float threshold = 0.5f;

        ImGui::BeginChild("Canvas", ImVec2(0, 0), 1, 0);
        auto   start_pos   = ImGui::GetCursorScreenPos();
        auto   drawList    = ImGui::GetWindowDrawList();
        ImVec2 window_size = ImGui::GetCurrentWindow()->Size;
        ImVec2 offset;
        ImVec2 map_size = ImVec2(map->size.x * bsize, map->size.y * bsize);
        if (window_size.x > map_size.x && window_size.y > map_size.y) {
            offset.x = (window_size.x - map_size.x) / 2 + start_pos.x;
            offset.y = (window_size.y - map_size.y) / 2 + start_pos.y;
        }

        for (int i = 0; i < map->size.y; i++) {
            for (int j = 0; j < map->size.x; j++) {
                ImVec2 p0 = {offset.x + j * bsize, offset.y + i * bsize};
                ImVec2 p1 = {offset.x + (j + 1) * bsize - 1.0f,
                             offset.y + (i + 1) * bsize - 1.0f};
                if (map->map[i][j] == MAP_EDGE) {
                    drawList->AddRectFilled(p0, p1,
                                            ImGui::ColorConvertFloat4ToU32(
                                                {1.0f, 1.0f, 1.0f, 0.4}));
                } else if (map->map[i][j] == MAP_RUBBISH) {
                    drawList->AddRectFilled(p0, p1,
                                            ImGui::ColorConvertFloat4ToU32(
                                                {1.0f, 0.0f, 0.0f, 0.5}));
                } else if (map->map[i][j] == MAP_EMPTY) {
                    drawList->AddRectFilled(p0, p1,
                                            ImGui::ColorConvertFloat4ToU32(
                                                {1.0f, 1.0f, 1.0f, 0.1}));
                } else if (map->map[i][j] == MAP_OUT) {
                    drawList->AddRectFilled(p0, p1,
                                            ImGui::ColorConvertFloat4ToU32(
                                                {1.0f, 1.0f, 1.0f, 0.0}));
                }
                // Hover
                // if (ImGui::IsMouseHoveringRect(p0, p1)) {
                //     if (ImGui::IsMouseClicked(0)) {
                //         map_editor->modifiedMap(*map, vec_2i(j, i));
                //     }
                // }
            }
        }

        ImGui::EndChild();
    }
    ImGui::End();
}