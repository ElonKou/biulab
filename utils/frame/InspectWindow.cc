/*================================================================
*  Copyright (C)2019 All rights reserved.
*  FileName : InspectWindow.cc
*  Author   : elonkou
*  Email    : elonkou@ktime.cc
*  Date     : 2019年12月28日 星期六 16时01分14秒
================================================================*/

#include "InspectWindow.hh"
#include "DynamicClass.hh"

void InspectInfo::AddInfo(string path, string pattern, bool target) {
    vector<string> names = GetFiles(path);
    InspectItem    item;
    for (size_t i = 0; i < names.size(); i++) {
        vector<string> name = Split(names[i], "/");
        item.data.push_back(name[name.size() - 1]);
        item.selected  = "";
        item.title     = pattern;
        item.collapsed = target;
    }
    items.insert({pattern, item});
}

void InspectInfo::UpdateFunc(string maps_path) {
    unordered_map<string, string> xx = {{"maps", ""}};
    overview_info->items.insert({"simplemap", xx});
    overview_info->items["simplemap"]["maps"] = items["maps"].selected;
    if (items.size() > 0 && items["maps"].changed) {
        string map_name_ = items["maps"].selected;
        if (map_name_.size() > 0) {
            items["maps"].changed = false;
            simple_map->LoadMap(maps_path + "/" + map_name_);
        }
    }
}

InspectWindow::InspectWindow() {}

InspectWindow::~InspectWindow() {}

void InspectWindow::Show() {
    if (ImGui::Begin("Inspector", &manager->options.show_inspector_window, 0)) {
        if (!info) {
            return;
        }
        for (auto it = info->items.begin(); it != info->items.end(); it++) {
            ImGui::SetNextItemOpen(!it->second.collapsed, ImGuiCond_Once);
            InspectItem& item = it->second;
            if (ImGui::TreeNode(item.title.c_str())) {
                for (size_t j = 0; j < item.data.size(); j++) {
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
