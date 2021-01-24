/*================================================================
*  Copyright (C)2019 All rights reserved.
*  FileName : core/Menu.cc
*  Author   : elonkou
*  Email    : elonkou@ktime.cc
*  Date     : 2019年11月11日 星期一 22时51分36秒
================================================================*/

#include "Menu.hh"
#include "DynamicClass.hh"

Menu::Menu() {}

Menu::Menu(ModulesManager* man) {
    manager = man;
}

Menu::~Menu() {}

void Menu::ShowMenuFile() {
    if (ImGui::BeginMenu("Open Modules", "Ctrl+O")) {
        for (size_t i = 0; i < manager->modules_info.size(); i++) {
            if (ImGui::MenuItem(manager->modules_info[i].module_name.c_str(), NULL, manager->modules_info[i].running)) {
                manager->options.show_program_window = false;
                manager->LoadModule(manager->modules_info[i].module_name);
            }
        }
        ImGui::EndMenu();
    }
    if (ImGui::MenuItem("Save", "Ctrl+S")) {
    }
    if (ImGui::MenuItem("Save As..")) {
    }
    ImGui::Separator();
    if (ImGui::BeginMenu("Preferences")) {
        static bool enabled = true;
        ImGui::MenuItem("auto save", "", &enabled);
        ImGui::MenuItem("Author");
        ImGui::EndMenu();
    }
    if (ImGui::BeginMenu("Colors")) {
        float sz = ImGui::GetTextLineHeight();
        for (int i = 0; i < ImGuiCol_COUNT; i++) {
            const char* name = ImGui::GetStyleColorName((ImGuiCol)i);
            ImVec2      p    = ImGui::GetCursorScreenPos();
            ImGui::GetWindowDrawList()->AddRectFilled(
                p, ImVec2(p.x + sz, p.y + sz), ImGui::GetColorU32((ImGuiCol)i));
            ImGui::Dummy(ImVec2(sz, sz));
            ImGui::SameLine();
            ImGui::MenuItem(name);
        }
        ImGui::EndMenu();
    }
    if (ImGui::MenuItem("Quit", "Alt+F4")) {
        manager->QuitModule();
        manager->options.show_program_window = true;
    }
}

void Menu::Show() {
    if (ImGui::BeginMainMenuBar()) {
        if (ImGui::BeginMenu("File")) {
            ShowMenuFile();
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Edit")) {
            if (ImGui::MenuItem("Undo", "CTRL+Z")) {
            }
            if (ImGui::MenuItem("Redo", "CTRL+Y", false, false)) {
            }
            ImGui::Separator();
            if (ImGui::MenuItem("Copy", "CTRL+C")) {
            }
            if (ImGui::MenuItem("Cut", "CTRL+X")) {
            }
            if (ImGui::MenuItem("Paste", "CTRL+V")) {
            }
            ImGui::EndMenu();
        }
    }

    if (ImGui::BeginMenu("View")) {
        if (ImGui::MenuItem("Control")) {
            manager->options.show_control_window = !manager->options.show_control_window;
        }
        if (ImGui::MenuItem("Display")) {
            manager->options.show_map_window = !manager->options.show_map_window;
        }
        if (ImGui::MenuItem("Overview")) {
            manager->options.show_overlay_window = !manager->options.show_overlay_window;
        }
        if (ImGui::MenuItem("Node view")) {
            manager->options.show_node_window = !manager->options.show_node_window;
        }
        if (ImGui::MenuItem("Inspector")) {
            manager->options.show_inspector_window = !manager->options.show_inspector_window;
        }
        if (ImGui::MenuItem("Graph")) {
            manager->options.show_graph_window = !manager->options.show_graph_window;
        }
        if (ImGui::MenuItem("Editor")) {
            manager->options.show_mapeditor_window = !manager->options.show_mapeditor_window;
        }
        if (ImGui::MenuItem("Demo")) {
            manager->options.show_demo_window = !manager->options.show_demo_window;
        }
        ImGui::EndMenu();
    }
    if (ImGui::BeginMenu("Theme")) {
        if (ImGui::MenuItem("Dark theme")) {
        }
        if (ImGui::MenuItem("Light theme")) {
        }
        if (ImGui::MenuItem("Github theme")) {
        }
        ImGui::EndMenu();
    }
    if (ImGui::BeginMenu("help")) {
        if (ImGui::MenuItem("Simple")) {
        }
        ImGui::SameLine();
        showHelpMarker("This is a simple text for help.");
        ImGui::EndMenu();
    }
    ImGui::EndMainMenuBar();
}
