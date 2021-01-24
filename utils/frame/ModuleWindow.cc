/*================================================================
*  Copyright (C)2020 All rights reserved.
*  FileName : ModuleWindow.cc
*  Author   : elonkou
*  Email    : elonkou@ktime.cc
*  Date     : 2020年02月14日 星期五 12时28分44秒
================================================================*/

#include "ModuleWindow.hh"

ModuleWindow::ModuleWindow() {
}

ModuleWindow::ModuleWindow(ModulesManager* man) {
    manager = man;
}

ModuleWindow::~ModuleWindow() {
}

void ModuleWindow::Show() {
    // int flag = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoDocking ;
    int flag = ImGuiWindowFlags_NoTitleBar;
    if (ImGui::Begin("Program", &manager->options.show_program_window, flag)) {
        // ImGuiIO& io = ImGui::GetIO();
        for (size_t i = 0; i < manager->modules_info.size(); i++) {
            ImVec2ih uv = ImVec2ih(2, 4);
            ImGui::ThumbNail((void*)(intptr_t)manager->modules_info[i].icon_id, ImVec2(160, 160), manager->modules_info[i].module_name, uv, i);
            // ImVec2 pos = ImGui::GetCursorScreenPos();
            if (ImGui::IsItemHovered()) {
                if (ImGui::IsMouseDoubleClicked(0)) {
                    manager->options.show_program_window = false;
                    manager->LoadModule(manager->modules_info[i].module_name);
                }
                // ImGui::BeginTooltip();
                // float region_sz = 32.0f;
                // float region_x  = io.MousePos.x - pos.x - region_sz * 0.5f;
                // if (region_x < 0.0f)
                //     region_x = 0.0f;
                // else if (region_x > 160 - region_sz)
                //     region_x   = 160 - region_sz;
                // float region_y = io.MousePos.y - pos.y - region_sz * 0.5f;
                // if (region_y < 0.0f)
                //     region_y = 0.0f;
                // else if (region_y > 90 - region_sz)
                //     region_y = 90 - region_sz;
                // ImGui::EndTooltip();
            }
        }
        ImGui::End();
    }
}
