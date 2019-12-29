/*================================================================
*  Copyright (C)2019 All rights reserved.
*  FileName : MapEditorWindow.cc
*  Author   : elonkou
*  Email    : elonkou@ktime.cc
*  Date     : 2019年10月05日 星期六 16时07分35秒
================================================================*/

#include "MapEditorWindow.hh"
#include <iostream>
#include "DynamicClass.hh"

using namespace std;

DYN_DECLARE(MapEditorWindow);

MapEditorWindow::MapEditorWindow() {}

MapEditorWindow::~MapEditorWindow() {}

void MapEditorWindow::show() {
    if (ImGui::Begin("Editor", &show_editor_window, 0)) {
        ImGui::SetNextItemOpen(true, ImGuiCond_Once);
        if (ImGui::TreeNode("Map editor")) {
            // Base
            {
                static bool has_create_map = false;
                static bool has_saved_map = false;
                if (ImGui::Button("Create Map")) {
                    // if (!has_create_map) {
                    //     has_create_map = true;
                    //     SimpleMap* empty_map =
                    //         new SimpleMap(vec_2i(MAP_WIDTH, MAP_HEIGHT));
                    //     setMap(empty_map);
                    // }
                }
                ImGui::SameLine();
                if (ImGui::Button("Save")) {
                    // if (has_map) {
                    //     string full_path =
                    //         string(con->map_path) + "/" + string(con->map_name);
                    //     map->saveMap(full_path);
                    //     has_map = false;
                    //     has_create_map = false;
                    // }
                }
                // ImGui::BulletText("Base:");
                // ImGui::InputText("Save name", con->map_name,
                //                  IM_ARRAYSIZE(con->map_name));
                // if (ImGui::InputInt("Width", &mapEditor->width, 1, 2)) {
                //     mapEditor->updateMap(*map);
                // }
                // if (ImGui::InputInt("Height", &mapEditor->height, 1, 2)) {
                //     mapEditor->updateMap(*map);
                // }
            }
            ImGui::Separator();
            // Tools
            // {
            //     ImGui::BulletText("Tools:");
            //     ImGui::PushID(0);
            //     ImGui::PushStyleColor(ImGuiCol_Button,
            //                           (ImVec4)ImColor::HSV(0.7f, 0.5f, 0.6f));
            //     ImGui::PushStyleColor(ImGuiCol_ButtonHovered,
            //                           (ImVec4)ImColor::HSV(0.7f, 0.5f, 0.7f));
            //     ImGui::PushStyleColor(ImGuiCol_ButtonActive,
            //                           (ImVec4)ImColor::HSV(0.9f, 0.5f, 0.8f));
            //     if (ImGui::Button("None")) {
            //         mapEditor->setTools(T_NONE);
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
            //         mapEditor->setTools(T_EDGE);
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
            //         mapEditor->setTools(T_RUBBISH);
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
            //         mapEditor->setTools(T_OUT);
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
            //         mapEditor->setTools(T_EMPTY);
            //     }
            //     ImGui::PopStyleColor(3);
            //     ImGui::PopID();
            // }
            // ImGui::Separator();
            // // Selections.
            // {
            //     ImGui::BulletText("Selection:");
            //     if (ImGui::Button("None")) {
            //         mapEditor->setSelection(S_NONE);
            //     }
            //     ImGui::SameLine();
            //     if (ImGui::Button("Point")) {
            //         mapEditor->setSelection(S_POINT);
            //     }
            //     ImGui::SameLine();
            //     if (ImGui::Button("Line")) {
            //         mapEditor->setSelection(S_LINE);
            //     }
            //     ImGui::SameLine();
            //     if (ImGui::Button("Rect")) {
            //         mapEditor->setSelection(S_RECT);
            //     }
            //     ImGui::SameLine();
            //     if (ImGui::Button("Block")) {
            //         mapEditor->setSelection(S_BLOCK);
            //     }
            //     ImGui::SameLine();
            //     if (ImGui::Button("All")) {
            //         mapEditor->setSelection(S_ALL);
            //     }
            // }
            ImGui::TreePop();
        }
    }
    ImGui::End();
}