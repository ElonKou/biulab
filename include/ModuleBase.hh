#pragma once
#ifndef MODULES_BASE_HH_
#define MODULES_BASE_HH_

#include "Base.hh"
#include "Lib.hh"
#include "PluginHelper.hh"
#include <iostream>
#include <vector>

class ModulesManager;

class ModuleBase : public Base {
  public:
    string module_name;

    ModulesManager* manager;

    ModuleBase() {}

    ~ModuleBase() {}

    virtual void InitModule() = 0;

    virtual void UpdateModule() = 0;
};

typedef struct MenuOptions {
    bool show_dock_space;
    bool show_main_window;
    bool show_demo_window;
    bool show_menu_bar;
    bool show_overlay_window;
    bool show_control_window;
    bool show_graph_window;
    bool show_node_window;
    bool show_inspector_window;
    bool show_mapeditor_window;
    bool show_map_window;
    bool show_program_window;
} MenuOptions;

typedef struct ModuleInfoData {
    string module_info;
    string module_name;
    string module_icon;
    string module_share;
    GLuint icon_id;
    ImVec2 icon_size;
    bool   loaded;
    bool   running;
} ModuleInfoData;

class ModulesManager {
  private:
    CPluginHelper pluginhelper;

    ModuleBase* module; // running module.

  public:
    vector<ModuleInfoData> modules_info;

    MenuOptions options;

    ModulesManager();

    ~ModulesManager();

    bool LoadModule(string module_name);

    bool UnloadModule(string module_name);

    bool QuitModule();

    void UpdateModule();

    void GetConfigs();
};
#endif