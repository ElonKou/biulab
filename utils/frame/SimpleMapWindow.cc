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
}
SimpleMapWindow::SimpleMapWindow(ModulesManager* man) {
    bsize      = 16.0f;
    padding    = 1.0f;
    simple_map = nullptr;
    // map_editor = nullptr;
    manager = man;
}

SimpleMapWindow::~SimpleMapWindow() {}

void SimpleMapWindow::Show() {
    if (!simple_map) {
        return;
    }
    if (ImGui::Begin("Simple Map", &manager->options.show_map_window, 0)) {
        ImGui::BeginChild("Canvas", ImVec2(0, 0), 1, 0);
        ImGuiIO&      io          = ImGui::GetIO();
        // static ImVec2 last_pos    = ImVec2(-1, -1);
        // static int    last_cnt    = 0;
        auto          start_pos   = ImGui::GetCursorScreenPos();
        auto          drawList    = ImGui::GetWindowDrawList();
        ImVec2        window_size = ImGui::GetCurrentWindow()->Size;
        ImVec2        map_size    = ImVec2(simple_map->size.x * bsize, simple_map->size.y * bsize);
        ImVec2        end_pos     = ImVec2(start_pos.x + window_size.x, start_pos.y + window_size.y);
        ImVec2        offset      = ImVec2((window_size.x - map_size.x) / 2 + start_pos.x, (window_size.y - map_size.y) / 2 + start_pos.y);
        for (int i = 0; i < simple_map->size.y; i++) {
            for (int j = 0; j < simple_map->size.x; j++) {
                ImVec2 p0    = {offset.x + j * bsize, offset.y + i * bsize};
                ImVec2 p1    = {offset.x + (j + 1) * bsize - padding, offset.y + (i + 1) * bsize - padding};
                ImVec4 color = simple_map->infos[int(simple_map->target[i][j])].color;
                // Hover& click event
                if (ImGui::IsMouseHoveringRect(p0, p1)) {
                    color.w = color.w < 1.0 ? color.w + 0.1 : color.w - 0.1;
                    // if (ImGui::IsMouseClicked(0) && map_editor) {
                    //     map_editor->ModifiedMap(*simple_map, vec_2i(j, i));
                    //     if ((map_editor->selections == S_LINE || map_editor->selections == S_RECT) && last_cnt == 0) {
                    //         last_cnt++;
                    //         last_pos = ImVec2(i, j);
                    //     } else if (last_cnt == 1) {
                    //         last_pos = ImVec2(-1, -1);
                    //         last_cnt = 0;
                    //     }
                    // }
                    {
                        // show position in tools tip.
                        ImVec2 pos = ImGui::GetCursorScreenPos();
                        ImGui::BeginTooltip();
                        float region_sz = 32.0f;
                        float region_x  = io.MousePos.x - pos.x - region_sz * 0.5f;
                        if (region_x < 0.0f)
                            region_x = 0.0f;
                        else if (region_x > 160 - region_sz)
                            region_x   = 160 - region_sz;
                        float region_y = io.MousePos.y - pos.y - region_sz * 0.5f;
                        if (region_y < 0.0f)
                            region_y = 0.0f;
                        else if (region_y > 90 - region_sz)
                            region_y = 90 - region_sz;
                        ImGui::Text("(%d, %d)", j, i);
                        ImGui::EndTooltip();
                    }
                }
                // if (last_pos.x == i && last_pos.y == j) {
                //     color.w = color.w < 1.0 ? color.w + 0.1 : color.w - 0.1;
                // }
                if (simple_map->only_show_round && simple_map->render_target.size() > 0) {
                    vec_2i act = vec_2i(-10, -10);
                    for (size_t k = 0; k < simple_map->render_target.size(); k++) {
                        if (simple_map->render_target[k].p_type == PATH_ACTOR && simple_map->render_target[k].positions.size() > 0) {
                            act = simple_map->render_target[k].positions[0];
                            continue;
                        }
                    }
                    vec_2i off = vec_2i(j, i) - act;
                    if (off == vec_2i(1, 0) || off == vec_2i(-1, 0) || off == vec_2i(0, -1) || off == vec_2i(0, 1)) {
                        drawList->AddRectFilled(p0, p1, ImGui::ColorConvertFloat4ToU32(color));
                    }
                } else {
                    drawList->AddRectFilled(p0, p1, ImGui::ColorConvertFloat4ToU32(color));
                }
            }
        }
        // render targets
        float c_radius = 3;
        for (size_t i = 0; i < simple_map->render_target.size(); i++) {
            PathType pt = simple_map->render_target[i].p_type;
            ImVec2   last_center;
            for (size_t j = 0; j < simple_map->render_target[i].positions.size(); j++) {
                vec_2i tar_pos   = simple_map->render_target[i].positions[j];
                ImVec2 p0        = {offset.x + tar_pos.x * bsize, offset.y + tar_pos.y * bsize};
                ImVec2 p1        = {offset.x + (tar_pos.x + 1) * bsize - padding, offset.y + (tar_pos.y + 1) * bsize - padding};
                ImVec2 center    = (p0 + p1) / 2;
                ImVec4 cir_color = simple_map->info_target[int(pt)].color;
                if (pt == PATH_ACTOR) {
                    ImGui::DrawRobbie(drawList, p0, p1, cir_color);
                }
                if (pt == PATH_HISTORY) {
                    if (j != 0) {
                        drawList->AddLine(last_center, center, ImGui::ColorConvertFloat4ToU32(cir_color), 2);
                    }
                    drawList->AddCircleFilled(center, c_radius, ImGui::ColorConvertFloat4ToU32(cir_color));
                }
                last_center = center;
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