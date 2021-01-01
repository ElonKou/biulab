#pragma once
#ifndef MODULES_MANAGER_HH_
#define MODULES_MANAGER_HH_

#include "Lib.hh"
#include "ModuleBase.hh"
#include "PluginHelper.hh"
#include <vector>

using namespace std;

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

    ModulesManager();

    ~ModulesManager();

    bool LoadModule(string module_name);

    bool UnloadModule(string module_name);

    bool QuitModule();

    void UpdateModule();

    void GetAllModules();
};

#endif