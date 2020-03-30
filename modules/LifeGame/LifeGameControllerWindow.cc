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
    static int lf_rate    = 50;
    static int lf_rule    = 30;
    static int lf_width   = 128;
    static int lf_history = 64;
    if (ImGui::Begin("LifeGameControllerWindow", &show_control_window, 0)) {
        // rate
        if (ImGui::Button("Ret")) {
            lf_rate = 50;
        }
        ImGui::SameLine();
        if (ImGui::InputInt("Rate", &lf_rate, 1, 2)) {
            lf_rate = min(lf_rate, 100);
            lf_rate = max(lf_rate, 0);
        }
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
            lf_width = 64;
        }
        ImGui::SameLine();
        if (ImGui::InputInt("width", &lf_width, 1, 2)) {
            lf_width = min(lf_width, 256);
            lf_width = max(lf_width, 16);
        }
        // hisrory
        if (ImGui::Button("Ret")) {
            lf_history = 64;
        }
        ImGui::SameLine();
        if (ImGui::InputInt("history", &lf_history, 1, 2)) {
            lf_history = min(lf_history, 256);
            lf_history = max(lf_history, 16);
        }
        if (ImGui::Button("Init")) {
            con->UpdateSize(lf_width, lf_history);
        }
        ImGui::SameLine();
        if (ImGui::Button("Random")) {
            con->RandomElems(lf_rate);
        }
        ImGui::SameLine();
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
        // show rules
        // TODO
    }
    ImGui::End();
}

void LifeGameControllerWindow::UpdateData() {
    con            = GetData<LifeGameController>("LifeGameController", "LifeGameControllerWindow");
    con->map_base  = GetData<LifeGameMapBase>("LifeGameMapBase", "LifeGameControlWindow");
    con->rule_base = GetData<LifeGameRuleBase>("LifeGameRuleBase", "LifeGameControlWindow");
}