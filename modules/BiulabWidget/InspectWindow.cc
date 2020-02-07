/*================================================================
*  Copyright (C)2019 All rights reserved.
*  FileName : InspectWindow.cc
*  Author   : elonkou
*  Email    : elonkou@ktime.cc
*  Date     : 2019年12月28日 星期六 16时01分14秒
================================================================*/

#include "InspectWindow.hh"
#include "DynamicClass.hh"

DYN_DECLARE(InspectWindow);

InspectWindow::InspectWindow() {}

InspectWindow::~InspectWindow() {}

void InspectWindow::Show() {
    if (ImGui::Begin("Inspector", &show_inspector_window, 0)) {
        for (auto it = info->items.begin(); it != info->items.end(); it++) {
            ImGui::SetNextItemOpen(!it->second.collapsed, ImGuiCond_Once);
            InspectItem& item = it->second;
            if (ImGui::TreeNode(item.title.c_str())) {
                for (int j = 0; j < item.data.size(); j++) {
                    string list_name = item.data[j];
                    if (ImGui::Selectable(list_name.c_str(), item.data[j] == item.selected, ImGuiSelectableFlags_AllowDoubleClick)) {
                        if (ImGui::IsMouseDoubleClicked(0)) {
                            item.selected = list_name;
                            item.changed  = true;
                        }
                    }
                }
                ImGui::TreePop();
            }
        }
    }
    ImGui::End();
}

void InspectWindow::UpdateData() {
    info = GetData<InspectInfo>("InspectInfo");
}
