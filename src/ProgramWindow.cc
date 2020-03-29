/*================================================================
*  Copyright (C)2020 All rights reserved.
*  FileName : ProgramWindow.cc
*  Author   : elonkou
*  Email    : elonkou@ktime.cc
*  Date     : 2020年02月14日 星期五 12时28分44秒
================================================================*/

#include "ProgramWindow.hh"

ProgramWindow::ProgramWindow() {
    fstream fp;
    string  line;
    fp.open(BIULAB_MODULES_PATH "/ProgramConfig.ini", ios::in);
    while (getline(fp, line)) {
        ProgramWindowData elem;
        if (line.size() > 0 && line[0] != ';' && line[0] != ' ') {
            elem.program_name = Split(line, ":")[0] + "Module";
            getline(fp, line);
            elem.dependences = Split(Split(line, ":")[1], ",");
            getline(fp, line);
            elem.program_info = Split(line, ":")[1];
            getline(fp, line);
            elem.program_icon = Split(line, ":")[1];
            int limit         = 20;
            for (int i = 1; i <= elem.program_info.size() / limit; i++) {
                int offset = 0;
                while (offset < limit && elem.program_info[i * limit - offset] != ' ') {
                    offset++;
                }
                if (offset == limit) {
                    elem.program_info.insert(elem.program_info.begin() + i * limit, '\n');
                } else {
                    elem.program_info[i * limit - offset] = '\n';
                }
            }
            int    width     = 0;
            int    height    = 0;
            string icon_path = BIULAB_INSTALL_PATH + string("/resources/icons/") + elem.program_icon;
            bool   ret       = LoadTextureFromFile(icon_path.c_str(), &elem.tex_id, &width, &height);
            elem.size        = ImVec2(width, height);
            data.push_back(elem);
        }
    }
    fp.close();
}

ProgramWindow::~ProgramWindow() {
}

void ProgramWindow::Show() {
    // int flag = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoDocking ;
    int flag = ImGuiWindowFlags_NoTitleBar;
    if (ImGui::Begin("Program", &show_program_window, flag)) {
        ImGuiIO& io = ImGui::GetIO();
        for (size_t i = 0; i < data.size(); i++) {
            ImVec2ih uv = ImVec2ih(2, 4);
            ImGui::ThumbNail((void*)(intptr_t)data[i].tex_id, ImVec2(160, 160), data[i].program_name, uv, i);
            ImVec2 pos = ImGui::GetCursorScreenPos();
            if (ImGui::IsItemHovered()) {
                if (ImGui::IsMouseDoubleClicked(0)) {
                    show_program_window = false;
                    manager->LoadProgram(data[i].dependences);
                }
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
                for (size_t j = 0; j < data[i].dependences.size(); j++) {
                    ImGui::Text("Module: %s", data[i].dependences[j].c_str());
                }
                ImGui::EndTooltip();
            }
        }
        ImGui::End();
    }
}

void ProgramWindow::UpdateData() {}