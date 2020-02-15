#pragma once
#ifndef MODULES_MANAGER_H_
#define MODULES_MANAGER_H_

#include "DataManager.hh"
#include "Lib.hh"
#include "ModuleBase.hh"
#include "PluginHelper.hh"
#include <vector>

using namespace std;

class ModulesManager {
  private:
    CPluginHelper pluginhelper;

    vector<ModuleBase*> modules;

  public:
    unordered_map<string, bool> modules_info;

    ModulesManager();

    ~ModulesManager();

    bool LoadModule(string module_name);

    bool UnloadModule(string module_name);

    void UpdateModule();

    void LoadProgram(vector<string> &program_modules);

    void UpdateData();

    void GetAllModules();
};

#endif