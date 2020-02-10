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
    simple_map = GetData<SimpleMap>("SimpleMap", "SimpleMapWindow");
    map_editor = GetData<MapEditorBase>("MapEditor", "SimpleMapWindow");
}

void SimpleMapWindow::Show() {
    if (!simple_map) {
        return;
    }
    if (ImGui::Begin("Simple Map", &show_simplemap_window, 0)) {
        ImGui::BeginChild("Canvas", ImVec2(0, 0), 1, 0);
        static ImVec2 last_pos    = ImVec2(-1, -1);
        static int    last_cnt    = 0;
        auto          start_pos   = ImGui::GetCursorScreenPos();
        auto          drawList    = ImGui::GetWindowDrawList();
        ImVec2        window_size = ImGui::GetCurrentWindow()->Size;
        ImVec2        map_size    = ImVec2(simple_map->size.x * bsize, simple_map->size.y * bsize);
        ImVec2        end_pos     = ImVec2(start_pos.x + window_size.x, start_pos.y + window_size.y);
        ImVec2        offset      = ImVec2((window_size.x - map_size.x) / 2 + start_pos.x, (window_size.y - map_size.y) / 2 + start_pos.y);

        for (int i = 0; i < simple_map->size.y; i++) {
            for (int j = 0; j < simple_map->size.x; j++) {
                ImVec2 p0 = {offset.x + j * bsize, offset.y + i * bsize};
                ImVec2 p1 = {offset.x + (j + 1) * bsize - padding, offset.y + (i + 1) * bsize - padding};
                ImVec4 color;
                color = simple_map->infos[int(simple_map->map[i][j])].color;
                // Hover& click event
                if (ImGui::IsMouseHoveringRect(p0, p1)) {
                    color.w = color.w < 1.0 ? color.w + 0.1 : color.w - 0.1;
                    if (ImGui::IsMouseClicked(0) && map_editor) {
                        map_editor->ModifiedMap(*simple_map, vec_2i(j, i));
                        if ((map_editor->selections == S_LINE || map_editor->selections == S_RECT) && last_cnt == 0) {
                            last_cnt++;
                            last_pos = ImVec2(i, j);
                        } else if (last_cnt == 1) {
                            last_pos = ImVec2(-1, -1);
                            last_cnt = 0;
                        }
                    }
                }
                if (last_pos.x == i && last_pos.y == j) {
                    color.w = color.w < 1.0 ? color.w + 0.1 : color.w - 0.1;
                }
                drawList->AddRectFilled(p0, p1, ImGui::ColorConvertFloat4ToU32(color));
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