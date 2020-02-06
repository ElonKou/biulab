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
    has_map        = false;
    has_create_map = false;
    has_saved_map  = false;
    map_changed    = false;
    simple_map     = nullptr;
    map_editor     = nullptr;
}

MapEditorWindow::~MapEditorWindow() {}

void MapEditorWindow::show() {
    if (!map_editor) {
        return;
    }
    if (ImGui::Begin("Editor", &show_editor_window, 0)) {
        ImGui::SetNextItemOpen(true, ImGuiCond_Once);
        if (ImGui::TreeNode("Map editor")) {
            // Base
            {
                if (ImGui::Button("Random")) {
                    if (has_map) {
                        simple_map->RandomMap();
                    }
                }
                ImGui::SameLine();
                if (ImGui::Button("Create")) {
                    if (!has_create_map) {
                        has_create_map = true;
                        has_map        = true;
                        simple_map->init();
                    }
                }
                ImGui::SameLine();
                if (ImGui::Button("Save")) {
                    if (has_map) {
                        string map_name_ = string(temp_name);
                        string full_path;
                        if (map_name_.size() == 0) {
                            full_path = simple_map->path_name + "/maps/" + simple_map->map_name;
                        } else {
                            full_path = simple_map->path_name + "/maps/" + map_name_;
                        }
                        simple_map->saveMap(full_path);
                        has_map        = false;
                        has_create_map = false;
                    }
                }
                ImGui::InputText("Save name", temp_name, IM_ARRAYSIZE(temp_name));
                if (ImGui::InputInt("Width", &map_editor->width, 1, 2)) {
                    map_editor->updateMap(*simple_map);
                }
                if (ImGui::InputInt("Height", &map_editor->height, 1, 2)) {
                    map_editor->updateMap(*simple_map);
                }
            }
            // Tools
            {
                static int tool_id = 0;
                if (ImGui::RadioButton("None", &tool_id, 0)) {
                    map_editor->setTools(T_NONE);
                }
                ImGui::SameLine();
                if (ImGui::RadioButton("Edge", &tool_id, 1)) {
                    map_editor->setTools(T_EDGE);
                }
                ImGui::SameLine();
                if (ImGui::RadioButton("Rubbish", &tool_id, 2)) {
                    map_editor->setTools(T_RUBBISH);
                }
                ImGui::SameLine();
                if (ImGui::RadioButton("Out", &tool_id, 3)) {
                    map_editor->setTools(T_OUT);
                }
                ImGui::SameLine();
                if (ImGui::RadioButton("Empty", &tool_id, 4)) {
                    map_editor->setTools(T_EMPTY);
                }
            }
            // Selections.
            {
                static int selection_id = 0;
                if (ImGui::RadioButton("None", &selection_id, 0)) {
                    map_editor->setSelection(S_NONE);
                }
                ImGui::SameLine();
                if (ImGui::RadioButton("Point", &selection_id, 1)) {
                    map_editor->setSelection(S_POINT);
                }
                ImGui::SameLine();
                if (ImGui::RadioButton("Line", &selection_id, 2)) {
                    map_editor->setSelection(S_LINE);
                }
                ImGui::SameLine();
                if (ImGui::RadioButton("Rect", &selection_id, 3)) {
                    map_editor->setSelection(S_RECT);
                }
                ImGui::SameLine();
                if (ImGui::RadioButton("Block", &selection_id, 4)) {
                    map_editor->setSelection(S_BLOCK);
                }
                ImGui::SameLine();
                if (ImGui::RadioButton("All", &selection_id, 5)) {
                    map_editor->setSelection(S_ALL);
                }
            }
            ImGui::TreePop();
        }
    }
    ImGui::End();
}

void MapEditorWindow::SetCores(MapEditor* map_editor_, SimpleMap* simple_map_) {
    map_editor = map_editor_;
    simple_map = simple_map_;
    has_map    = true;
}

void MapEditorWindow::ClearCores() {
    map_editor = nullptr;
    simple_map = nullptr;
}