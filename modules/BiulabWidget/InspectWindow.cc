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

void InspectWindow::show() {
    if (ImGui::Begin("Inspector", &show_inspector_window, 0)) {
        for (size_t i = 0; i < item_list.items.size(); i++) {
            ImGui::SetNextItemOpen(item_list.items[i].collapsed, ImGuiCond_Once);
            InspectItem& item = item_list.items[i];
            if (ImGui::TreeNode(item.title.c_str())) {
                for (int j = 0; j < item.data.size(); j++) {
                    string list_name = item.data[j];
                    if (ImGui::Selectable(list_name.c_str(), item.data[j] == item.selected, ImGuiSelectableFlags_AllowDoubleClick)) {
                        if (ImGui::IsMouseDoubleClicked(0)) {
                            item.selected = list_name;
                            item.index    = j;
                            // simple_map->loadMap(BIULAB_APPLICATION_PATH "/../maps/" + list_name);
                        }
                    }
                }
                ImGui::TreePop();
            }
        }
    }
    ImGui::End();
}

void InspectWindow::updateInspectItemList(InspectList list) {
    item_list = list;
}
