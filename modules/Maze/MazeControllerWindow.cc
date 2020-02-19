/*================================================================
*  Copyright (C)2020 All rights reserved.
*  FileName : MazeControllerWindow.cc
*  Author   : elonkou
*  Email    : elonkou@ktime.cc
*  Date     : 2020年02月18日 星期二 19时58分23秒
================================================================*/

#include "MazeControllerWindow.hh"

MazeControllerWindow::MazeControllerWindow() {
}

MazeControllerWindow::~MazeControllerWindow() {
}

void MazeControllerWindow::Show() {
    if (!con) {
        return;
    }
    if (ImGui::Begin("MazeController")) {
        ImGui::SliderInt("speed", &con->speed, 1, 120, "%d");
        static int selection_algorithm = 0;
        if (ImGui::SmallRadioButton("RightFirst##A", &selection_algorithm, 0)) {
            con->per->algorithm_name = "RightFirst";
        }
        ImGui::SameLine();
        if (ImGui::SmallRadioButton("LeftFirst##A", &selection_algorithm, 1)) {
            con->per->algorithm_name = "LeftFirst";
        }
        if (con->running) {
            if (ImGui::Button("pause")) {
                con->running = false;
            }
            ImGui::SameLine();
            if (ImGui::Button("stop")) {
                con->running = false;
                con->stop    = true;
            }
        } else {
            if (ImGui::Button("start")) {
                con->running = true;
            }
        }
        ImGui::End();
    }
}

void MazeControllerWindow::UpdateData() {
    con = GetData<MazeController>("MazeController", "MazeControllerWindow");
}