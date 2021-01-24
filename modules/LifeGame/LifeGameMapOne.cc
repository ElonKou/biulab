/*================================================================
*  Copyright (C)2020 All rights reserved.
*  FileName : LifeGameMapOne.cc
*  Author   : elonkou
*  Email    : elonkou@ktime.cc
*  Date     : 2020年03月07日 星期六 00时47分50秒
================================================================*/

#include "LifeGameMapOne.hh"

LifeGameMapOne::LifeGameMapOne()
    : row(0) {
    bsize   = 8.0f;
    padding = 1.0f;
    width   = LIFE_GAME_DIM_WIDTH;
    heigth  = LIFE_GAME_DIM_HEIGHT;
    map     = new LifeGameElem*[heigth];
    RandomElems();
}

LifeGameMapOne::~LifeGameMapOne() {
}

void LifeGameMapOne::Show() {
    if (ImGui::Begin("LifeGameMapOne", &manager->options.show_map_window, 0)) {
        ImGui::BeginChild("Canvas", ImVec2(0, 0), 1, 0);
        auto   start_pos   = ImGui::GetCursorScreenPos();
        auto   drawList    = ImGui::GetWindowDrawList();
        ImVec2 window_size = ImGui::GetCurrentWindow()->Size;
        ImVec2 map_size    = ImVec2(width * bsize, row * bsize);
        ImVec2 offset      = ImVec2((window_size.x - map_size.x) / 2 + start_pos.x, (window_size.y - map_size.y) / 2 + start_pos.y);
        for (size_t j = 0; j < row; j++) {
            for (size_t i = 0; i < width; i++) {
                ImVec2 p0 = {offset.x + i * bsize, offset.y + j * bsize};
                ImVec2 p1 = {offset.x + (i + 1) * bsize - padding, offset.y + (j + 1) * bsize - padding};
                ImVec4 color;
                if (map[j][i] == ElemAlive) {
                    color = ImVec4(1.0, 1.0, 1.0, 0.6);
                } else {
                    color = ImVec4(0.0, 0.0, 0.0, 1.0);
                }
                // TODO:hover event
                drawList->AddRectFilled(p0, p1, ImGui::ColorConvertFloat4ToU32(color));
            }
        }
        ImGui::EndChild();
        if (ImGui::IsMouseHoveringRect(start_pos, start_pos + window_size)) {
            ImGuiIO& io = ImGui::GetIO();
            if (io.MouseWheel != 0.0) {
                bsize += io.MouseWheel;
                bsize = MAX(bsize, 1.0);
                bsize = MIN(bsize, 64);
                if (bsize < 5.0f) {
                    padding = 0.0f;
                } else {
                    padding = 1.0f;
                }
            }
        }
    }
    ImGui::End();
}

void LifeGameMapOne::UpdateSize(int _width, int _height) {
    width  = MIN(_width, LIFE_GAME_DIM_MAX);
    heigth = MIN(_height, LIFE_GAME_DIM_MAX);
    row    = 0;
    map    = new LifeGameElem*[heigth];
    RandomElems();
}

void LifeGameMapOne::RandomElems(int rate) {
    map[0] = new LifeGameElem[width];
    row    = 1;
    for (size_t i = 0; i < width; i++) {
        int rand = RandomInt(1000);
        if (rand < rate) {
            map[0][i] = ElemAlive;
        } else {
            map[0][i] = ElemDead;
        }
    }
}

void LifeGameMapOne::UpdateMap(LifeGameRuleBase& rule, int rule_id) {
    if (row < heigth) {
        map[row] = new LifeGameElem[width];
        for (size_t i = 0; i < width; i++) {
            vector<LifeGameElem> elems = {map[row - 1][(i - 1 + width) % width], map[row - 1][i], map[row - 1][(i + 1) % width]};
            map[row][i]                = rule.GetAction(rule_id, elems);
        }
        row++;
    }
}

vec_2i LifeGameMapOne::GetSize() {
    return vec_2i(width, row);
}