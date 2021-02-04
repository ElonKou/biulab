/*================================================================
*  Copyright (C)2020 All rights reserved.
*  FileName : LifeController.cc
*  Author   : elonkou
*  Email    : elonkou@ktime.cc
*  Date     : Mon 01 Feb 2021 05:04:18 PM CST
================================================================*/

#include "LifeController.hh"

LifeController::LifeController() {
}

LifeController::~LifeController() {
}

void LifeController::Show() {
    if (!life) {
        return;
    }
    if (ImGui::Begin("Life2DConWin", &manager->options.show_control_window, 0)) {
        if (ImGui::Button("run")) {
            life->run = !life->run;
        }
        ImGui::SliderInt("fps:", &life->fps, 1, 200);
    }
    ImGui::End();
}
