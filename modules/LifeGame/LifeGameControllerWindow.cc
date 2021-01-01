/*================================================================
*  Copyright (C)2020 All rights reserved.
*  FileName : LifeGameControllerWindow.cc
*  Author   : elonkou
*  Email    : elonkou@ktime.cc
*  Date     : 2020年02月23日 星期日 17时46分19秒
================================================================*/

#include "LifeGameControllerWindow.hh"

LifeGameControllerWindow::LifeGameControllerWindow() {
}

LifeGameControllerWindow::~LifeGameControllerWindow() {
}

void LifeGameControllerWindow::Show() {
    static float lf_rate   = 50.0f;
    static int   lf_rule   = 30;
    static int   lf_width  = LIFE_GAME_DIM_WIDTH;
    static int   lf_height = LIFE_GAME_DIM_HEIGHT;
    if (ImGui::Begin("LifeGameControllerWindow", &show_control_window, 0)) {
        // rate
        if (ImGui::Button("Ret")) {
            lf_rate = 50;
        }
        ImGui::SameLine();
        ImGui::SliderFloat("Rate", &lf_rate, 0.0f, 100.0f, "%.2f");
        // rule id
        if (ImGui::Button("Ret")) {
            lf_rule = 30;
        }
        ImGui::SameLine();
        if (ImGui::InputInt("Rule id", &lf_rule, 1, 2)) {
            lf_rule = min(lf_rule, 255);
            lf_rule = max(lf_rule, 0);
        }
        // width
        if (ImGui::Button("Ret")) {
            lf_width = LIFE_GAME_DIM_WIDTH;
        }
        ImGui::SameLine();
        if (ImGui::InputInt("width", &lf_width, 1, 2)) {
            lf_width = min(lf_width, LIFE_GAME_DIM_MAX);
            lf_width = max(lf_width, 1);
        }
        if (ImGui::Button("Ret")) {
            lf_height = LIFE_GAME_DIM_HEIGHT;
        }
        ImGui::SameLine();
        if (ImGui::InputInt("height", &lf_height, 1, 2)) {
            lf_height = min(lf_height, LIFE_GAME_DIM_MAX);
            lf_height = max(lf_height, 1);
        }
        if (ImGui::Button("Random")) {
            con->RandomElems(int(lf_rate * 10));
        }
        ImGui::SameLine();
        if (ImGui::Button("Init")) {
            con->UpdateSize(lf_width, lf_height);
        }
        if (ImGui::Button("Next")) {
            con->UpdateRule(lf_rule);
        }
        ImGui::SameLine();
        if (ImGui::Button("Next2")) {
            for (size_t i = 0; i < 2; i++) {
                con->UpdateRule(lf_rule);
            }
        }
        ImGui::SameLine();
        if (ImGui::Button("Next5")) {
            for (size_t i = 0; i < 5; i++) {
                con->UpdateRule(lf_rule);
            }
        }
        ImGui::SameLine();
        if (ImGui::Button("Next10")) {
            for (size_t i = 0; i < 10; i++) {
                con->UpdateRule(lf_rule);
            }
        }
        ImGui::SameLine();
        if (ImGui::Button("NextMax")) {
            con->UpdateRuleMax(lf_rule, lf_height);
        }
        // TODO: show rules
        vector<vector<LifeGameElem>> res      = con->rule_base->GetRuleList(lf_rule);
        float                        bsize    = 24.0f;
        float                        padding  = 2.0f;
        float                        margin   = 8.0f;
        auto                         offset   = ImGui::GetCursorScreenPos() + ImVec2(10.0, 10.0);
        auto                         drawList = ImGui::GetWindowDrawList();
        ImGui::BeginChild("Canvas", ImVec2(0, 0), 1, 0);
        for (size_t j = 0; j < res.size(); j++) {
            for (size_t i = 0; i < res[j].size(); i++) {
                ImVec2 p0 = {offset.x + i * bsize, offset.y + j * bsize};
                ImVec2 p1 = {offset.x + (i + 1) * bsize - padding, offset.y + (j + 1) * bsize - padding};
                p0 += ImVec2(0.0f, j * margin);
                p1 += ImVec2(0.0f, j * margin);
                ImVec4 color;
                if (i == res[j].size() - 1) {
                    p0 += ImVec2(20.0f, 0.0f);
                    p1 += ImVec2(20.0f, 0.0f);
                }
                if (res[j][i] == ElemAlive) {
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