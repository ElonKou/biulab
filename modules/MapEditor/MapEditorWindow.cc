/*================================================================
*  Copyright (C)2019 All rights reserved.
*  FileName : MapEditorWindow.cc
*  Author   : elonkou
*  Email    : elonkou@ktime.cc
*  Date     : 2019年10月05日 星期六 16时07分35秒
================================================================*/

#include "MapEditorWindow.hh"
#include "DynamicClass.hh"
#include "MapEditorModule.hh"
#include <iostream>

using namespace std;

DYN_DECLARE(MapEditorWindow);

MapEditorWindow::MapEditorWindow() {
    simple_map = nullptr;
    map_editor = nullptr;
}

MapEditorWindow::~MapEditorWindow() {}

void MapEditorWindow::Show() {
    if (!map_editor) {
        return;
    }
    if (ImGui::Begin("Editor", &show_mapeditor_window, 0)) {
        ImGui::SetNextItemOpen(true, ImGuiCond_Once);
        if (ImGui::TreeNode("Map editor")) {
            // Base
            {
                if (ImGui::Button("Random")) {
                    if (simple_map) {
                        simple_map->RandomMap();
                    }
                }
                ImGui::SameLine();
                if (ImGui::Button("Init")) {
                    simple_map->Init();
                }
                ImGui::SameLine();
                if (ImGui::Button("Save")) {
                    if (simple_map) {
                        string map_name_ = string(temp_name);
                        string full_path;
                        simple_map->map_name = string(temp_name);
                        if (map_name_.size() == 0) {
                            full_path = simple_map->path_name + "/maps/" + simple_map->map_name;
                        } else {
                            full_path = simple_map->path_name + "/maps/" + map_name_;
                        }
                        simple_map->SaveMap(full_path);
                    }
                }
                ImGui::InputText("Save name", temp_name, IM_ARRAYSIZE(temp_name));
                if (ImGui::InputInt("Width", &map_editor->width, 1, 2)) {
                    map_editor->UpdateMap(*simple_map);
                }
                if (ImGui::InputInt("Height", &map_editor->height, 1, 2)) {
                    map_editor->UpdateMap(*simple_map);
                }
            }
            // Tools
            {
                static int tool_id = 0;
                if (ImGui::ColorRadioButton("None##T", &tool_id, 0, map_editor->infos[int(T_NONE)].color)) {
                    map_editor->SetTools(T_NONE);
                }
                ImGui::SameLine();
                if (ImGui::ColorRadioButton("Edge##T", &tool_id, 1, map_editor->infos[int(T_EDGE)].color)) {
                    map_editor->SetTools(T_EDGE);
                }
                ImGui::SameLine();
                if (ImGui::ColorRadioButton("Rubbish##T", &tool_id, 2, map_editor->infos[int(T_RUBBISH)].color)) {
                    map_editor->SetTools(T_RUBBISH);
                }
                ImGui::SameLine();
                if (ImGui::ColorRadioButton("Empty##T", &tool_id, 3, map_editor->infos[int(T_EMPTY)].color)) {
                    map_editor->SetTools(T_EMPTY);
                }
                ImGui::SameLine();
                if (ImGui::ColorRadioButton("Out##T", &tool_id, 4, map_editor->infos[int(T_OUT)].color)) {
                    map_editor->SetTools(T_OUT);
                }
                ImGui::SameLine();
                if (ImGui::ColorRadioButton("Gem##T", &tool_id, 5, map_editor->infos[int(T_GEM)].color)) {
                    map_editor->SetTools(T_GEM);
                }
            }
            // Selections.
            {
                static int selection_id = 0;
                if (ImGui::SmallRadioButton("None##S", &selection_id, 0)) {
                    map_editor->SetSelection(S_NONE);
                }
                ImGui::SameLine();
                if (ImGui::SmallRadioButton("Point##S", &selection_id, 1)) {
                    map_editor->SetSelection(S_POINT);
                }
                ImGui::SameLine();
                if (ImGui::SmallRadioButton("Line##S", &selection_id, 2)) {
                    map_editor->SetSelection(S_LINE);
                }
                ImGui::SameLine();
                if (ImGui::SmallRadioButton("Rect##S", &selection_id, 3)) {
                    map_editor->SetSelection(S_RECT);
                }
                ImGui::SameLine();
                if (ImGui::SmallRadioButton("Block##S", &selection_id, 4)) {
                    map_editor->SetSelection(S_BLOCK);
                }
                ImGui::SameLine();
                if (ImGui::SmallRadioButton("All##S", &selection_id, 5)) {
                    map_editor->SetSelection(S_ALL);
                }
            }
            ImGui::TreePop();
        }
    }
    ImGui::End();
}

void MapEditorWindow::UpdateData() {
    simple_map = GetData<SimpleMap>("SimpleMap", "MapEditorWindow");
    map_editor = GetData<MapEditor>("MapEditor", "MapEditorWindow");
    strcpy(temp_name, simple_map->map_name.c_str());
}
