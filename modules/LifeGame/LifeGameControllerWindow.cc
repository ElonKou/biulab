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
    if (ImGui::Begin("LifeGameControllerWindow", &show_control_window, 0)) {
        if (ImGui::Button("dasda")) {
            cout << "control" << endl;
        }
    }
    ImGui::End();
}

void LifeGameControllerWindow::UpdateData() {
    con      = GetData<LifeGameController>("LifeGameController", "LifeGameControllerWindow");
    map_base = GetData<LifeGameMapBase>("LifeGameMapBase", "LifeGameControlWindow");
}