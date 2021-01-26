/*================================================================
*  Copyright (C)2020 All rights reserved.
*  FileName : MazeMapWindow.cc
*  Author   : elonkou
*  Email    : elonkou@ktime.cc
*  Date     : 2020年02月18日 星期二 19时54分29秒
================================================================*/

#include "MazeMapWindow.hh"

MazeMapWindow::MazeMapWindow() {
}

MazeMapWindow::MazeMapWindow(ModulesManager* man) {
    bsize    = 16.0f;
    padding  = 1.0f;
    maze_map = nullptr;
    manager  = man;
}

MazeMapWindow::~MazeMapWindow() {
}

void MazeMapWindow::Show() {
    if (!maze_map) {
        return;
    }
    if (ImGui::Begin("Maze Map", &manager->options.show_map_window, 0)) {
        ImGui::BeginChild("Canvas", ImVec2(0, 0), 1, 0);
        static vec_2i last_pos    = vec_2i(-1, -1);
        auto          start_pos   = ImGui::GetCursorScreenPos();
        auto          drawList    = ImGui::GetWindowDrawList();
        ImVec2        window_size = ImGui::GetCurrentWindow()->Size;
        ImVec2        map_size    = ImVec2(maze_map->size.x * bsize, maze_map->size.y * bsize);
        ImVec2        end_pos     = ImVec2(start_pos.x + window_size.x, start_pos.y + window_size.y);
        ImVec2        offset      = ImVec2((window_size.x - map_size.x) / 2 + start_pos.x, (window_size.y - map_size.y) / 2 + start_pos.y);
        for (int i = 0; i < maze_map->size.y; i++) {
            for (int j = 0; j < maze_map->size.x; j++) {
                ImVec2 p0    = {offset.x + j * bsize, offset.y + i * bsize};
                ImVec2 p1    = {offset.x + (j + 1) * bsize - padding, offset.y + (i + 1) * bsize - padding};
                ImVec4 color = maze_map->infos[int(maze_map->target[i][j])].color;
                // Hover& click event
                if (ImGui::IsMouseHoveringRect(p0, p1)) {
                    color.w = color.w < 1.0 ? color.w + 0.1 : color.w - 0.1;
                    if (ImGui::IsMouseClicked(1)) {
                        ImGui::OpenPopup("Set position");
                        last_pos = vec_2i(j, i);
                    }
                }
                if (maze_map->GetTarget(vec_2i(j, i)) == MAP_FLAG) {
                    ImGui::DrawFlag(drawList, p0, p1, color);
                } else if (maze_map->GetTarget(vec_2i(j, i)) == MAP_DOOR) {
                    ImGui::DrawDoor(drawList, p0, p1, color);
                } else {
                    drawList->AddRectFilled(p0, p1, ImGui::ColorConvertFloat4ToU32(color));
                }
            }
        }
        if (ImGui::BeginPopup("Set position")) {
            if (ImGui::MenuItem("Set Start")) {
                maze_map->SetStartPos(last_pos);
                per->cur_pos = last_pos;
            }
            if (ImGui::MenuItem("Set End")) {
                maze_map->SetEndPos(last_pos);
            }
            if (ImGui::MenuItem("Set direction")) {
                vec_2i off = last_pos - maze_map->start_pos;
                if (off.x > 0) {
                    per->forward = DIR_RIGHT;
                }
                if (off.x < 0) {
                    per->forward = DIR_LEFT;
                }
                if (off.y > 0) {
                    per->forward = DIR_DOWN;
                }
                if (off.y < 0) {
                    per->forward = DIR_UP;
                }
            }
            ImGui::EndPopup();
        }
        float c_radius = 3;
        for (size_t i = 0; i < maze_map->render_target.size(); i++) {
            PathType pt = maze_map->render_target[i].p_type;
            ImVec2   last_center;
            for (size_t j = 0; j < maze_map->render_target[i].positions.size(); j++) {
                vec_2i tar_pos   = maze_map->render_target[i].positions[j];
                ImVec2 p0        = {offset.x + tar_pos.x * bsize, offset.y + tar_pos.y * bsize};
                ImVec2 p1        = {offset.x + (tar_pos.x + 1) * bsize - padding, offset.y + (tar_pos.y + 1) * bsize - padding};
                ImVec2 center    = (p0 + p1) / 2;
                ImVec4 cir_color = maze_map->info_target[int(pt)].color;
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
