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
                        cout << "save" << endl;
                        // string full_path = string(con->map_path) + "/" + string(con->map_name);
                        // map->saveMap(full_path);
                        has_map        = false;
                        has_create_map = false;
                    }
                }
                // ImGui::InputText("Save name", temp_name, IM_ARRAYSIZE(temp_name));
                // map_name = simple_map->map_name = string(temp_name);
                // if (ImGui::InputInt("Width", &map_editor->width, 1, 2)) {
                //     map_editor->updateMap(*simple_map);
                // }
                // if (ImGui::InputInt("Height", &map_editor->height, 1, 2)) {
                //     map_editor->updateMap(*simple_map);
                // }
            }
            // ImGui::Separator();
            // Tools
            // {
            //     ImGui::PushID(0);
            //     ImGui::PushStyleColor(ImGuiCol_Button,
            //                           (ImVec4)ImColor::HSV(0.7f, 0.5f, 0.6f));
            //     ImGui::PushStyleColor(ImGuiCol_ButtonHovered,
            //                           (ImVec4)ImColor::HSV(0.7f, 0.5f, 0.7f));
            //     ImGui::PushStyleColor(ImGuiCol_ButtonActive,
            //                           (ImVec4)ImColor::HSV(0.9f, 0.5f, 0.8f));
            //     if (ImGui::Button("None")) {
            //         map_editor->setTools(T_NONE);
            //     }
            //     ImGui::PopStyleColor(3);
            //     ImGui::PopID();
            //     ImGui::SameLine();
            //     // ############################

            //     ImGui::PushID(1);
            //     ImGui::PushStyleColor(ImGuiCol_Button,
            //                           (ImVec4)ImColor::HSV(0.0f, 0.0f, 0.6f));
            //     ImGui::PushStyleColor(ImGuiCol_ButtonHovered,
            //                           (ImVec4)ImColor::HSV(0.0f, 0.0f, 0.7f));
            //     ImGui::PushStyleColor(ImGuiCol_ButtonActive,
            //                           (ImVec4)ImColor::HSV(0.0f, 0.0f, 0.8f));
            //     if (ImGui::Button("Edge")) {
            //         map_editor->setTools(T_EDGE);
            //     }
            //     ImGui::PopStyleColor(3);
            //     ImGui::PopID();
            //     ImGui::SameLine();
            //     // ############################

            //     ImGui::PushID(2);
            //     ImGui::PushStyleColor(ImGuiCol_Button,
            //                           (ImVec4)ImColor::HSV(0.0f, 0.6f, 0.7f));
            //     ImGui::PushStyleColor(ImGuiCol_ButtonHovered,
            //                           (ImVec4)ImColor::HSV(0.0f, 0.7f, 0.8f));
            //     ImGui::PushStyleColor(ImGuiCol_ButtonActive,
            //                           (ImVec4)ImColor::HSV(0.0f, 0.8f, 0.9f));
            //     if (ImGui::Button("Rubbish")) {
            //         map_editor->setTools(T_RUBBISH);
            //     }
            //     ImGui::PopStyleColor(3);
            //     ImGui::PopID();
            //     ImGui::SameLine();
            //     // ############################

            //     ImGui::PushID(3);
            //     ImGui::PushStyleColor(ImGuiCol_Button,
            //                           (ImVec4)ImColor::HSV(0.0f, 0.0f, 0.15f));
            //     ImGui::PushStyleColor(ImGuiCol_ButtonHovered,
            //                           (ImVec4)ImColor::HSV(0.0f, 0.0f, 0.19f));
            //     ImGui::PushStyleColor(ImGuiCol_ButtonActive,
            //                           (ImVec4)ImColor::HSV(0.0f, 0.0f, 0.21f));
            //     if (ImGui::Button("Out")) {
            //         map_editor->setTools(T_OUT);
            //     }
            //     ImGui::PopStyleColor(3);
            //     ImGui::SameLine();
            //     // ############################

            //     ImGui::PopID();
            //     ImGui::PushID(4);
            //     ImGui::PushStyleColor(ImGuiCol_Button,
            //                           (ImVec4)ImColor::HSV(0.0f, 0.0f, 0.3f));
            //     ImGui::PushStyleColor(ImGuiCol_ButtonHovered,
            //                           (ImVec4)ImColor::HSV(0.0f, 0.0f, 0.4f));
            //     ImGui::PushStyleColor(ImGuiCol_ButtonActive,
            //                           (ImVec4)ImColor::HSV(0.0f, 0.0f, 0.5f));
            //     if (ImGui::Button("Empty")) {
            //         map_editor->setTools(T_EMPTY);
            //     }
            //     ImGui::PopStyleColor(3);
            //     ImGui::PopID();
            // }
            // ImGui::Separator();
            // // Selections.
            // {
            //     if (ImGui::Button("None")) {
            //         map_editor->setSelection(S_NONE);
            //     }
            //     ImGui::SameLine();
            //     if (ImGui::Button("Point")) {
            //         map_editor->setSelection(S_POINT);
            //     }
            //     ImGui::SameLine();
            //     if (ImGui::Button("Line")) {
            //         map_editor->setSelection(S_LINE);
            //     }
            //     ImGui::SameLine();
            //     if (ImGui::Button("Rect")) {
            //         map_editor->setSelection(S_RECT);
            //     }
            //     ImGui::SameLine();
            //     if (ImGui::Button("Block")) {
            //         map_editor->setSelection(S_BLOCK);
            //     }
            //     ImGui::SameLine();
            //     if (ImGui::Button("All")) {
            //         map_editor->setSelection(S_ALL);
            //     }
            // }
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