#pragma once
#ifndef MENU_HH_
#define MENU_HH_

#include "ModulesManager.hh"
#include "WindowBase.hh"

typedef struct MenuOptions {
    bool show_dock_sapce;
    bool show_main_window;
    bool show_demo_window;
    bool show_main_menu_bar;
    bool show_overlay_window;
    bool show_control_window;
    bool show_graph_window;
    bool show_node_window;
    bool show_inspector_window;
    bool show_mapeditor_window;
    bool show_map_window;
    bool show_program_window;
} MenuOptions;

class Menu : public WindowBase {
  public:
    ModulesManager* manager;

    MenuOptions options;

    Menu();

    ~Menu();

    virtual void Show();

    void ShowMenuFile();
};

#endif