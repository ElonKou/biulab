/*================================================================
*  Copyright (C)2020 All rights reserved.
*  FileName : LifeGameMapOne.cc
*  Author   : elonkou
*  Email    : elonkou@ktime.cc
*  Date     : 2020年03月07日 星期六 00时47分50秒
================================================================*/

#include "LifeGameMapOne.hh"

LifeGameMapOne::LifeGameMapOne()
    : index(0) {
    bsize   = 8.0f;
    padding = 1.0f;
    history = LIFE_GAME_DIM_HEIGT;
    size    = LIFE_GAME_DIM_WIDTH;
    map     = new LifeGameElem*[size];
    RandomElems();
    // cout << "LifeGameMapOne" << endl;
}

LifeGameMapOne::LifeGameMapOne(size_t size_, size_t his_)
    : size(size_)
    , history(his_)
    , index(0) {
    bsize   = 8.0f;
    padding = 1.0f;
    map     = new LifeGameElem*[size];
    RandomElems();
}

LifeGameMapOne::~LifeGameMapOne() {
}

void LifeGameMapOne::Show() {
    if (ImGui::Begin("LifeGameMapOne", &show_mapeditor_window, 0)) {
        ImGui::BeginChild("Canvas", ImVec2(0, 0), 1, 0);
        auto   start_pos   = ImGui::GetCursorScreenPos();
        auto   drawList    = ImGui::GetWindowDrawList();
        ImVec2 window_size = ImGui::GetCurrentWindow()->Size;
        ImVec2 map_size    = ImVec2(size * bsize, history * bsize);
        ImVec2 end_pos     = ImVec2(start_pos.x + window_size.x, start_pos.y + window_size.y);
        ImVec2 offset      = ImVec2((window_size.x - map_size.x) / 2 + start_pos.x, (window_size.y - map_size.y) / 2 + start_pos.y);
        for (size_t j = 0; j < index; j++) {
            for (size_t i = 0; i < size; i++) {
                ImVec2 p0 = {offset.x + i * bsize, offset.y + j * bsize};
                ImVec2 p1 = {offset.x + (i + 1) * bsize - padding, offset.y + (j + 1) * bsize - padding};
                ImVec4 color;
                if (map[j][i] == ElemAlive) {
                    color = ImVec4(1.0, 1.0, 1.0, 0.6);
                } else {
                    color = ImVec4(0.0, 0.0, 0.0, 1.0);
                }
                drawList->AddRectFilled(p0, p1, ImGui::ColorConvertFloat4ToU32(color));
            }
        }
        ImGui::EndChild();
    }
    ImGui::End();
}

void LifeGameMapOne::UpdateData() {}

void LifeGameMapOne::UpdateSize(int width, int history_) {
    size    = width;
    history = history_;
    index   = 0;
    map     = new LifeGameElem*[size];
    RandomElems();
}

void LifeGameMapOne::RandomElems(int rate) {
    map[0] = new LifeGameElem[size];
    index  = 1;
    for (size_t i = 0; i < size; i++) {
        int rand = RandomInt(100);
        if (rand <= rate) {
            map[0][i] = ElemAlive;
        } else {
            map[0][i] = ElemDead;
        }
    }
}

void LifeGameMapOne::UpdateMap(LifeGameRuleBase& rule, int rule_id) {
    map[index] = new LifeGameElem[size];
    for (size_t i = 0; i < size; i++) {
        vector<LifeGameElem> elems = {map[index - 1][(i - 1 + size) % size], map[index - 1][i], map[index - 1][(i + 1) % size]};
        map[index][i]              = rule.GetAction(rule_id, elems);
    }
    index++;
}