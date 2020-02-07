#pragma once
#ifndef MODULES_MANAGER_H_
#define MODULES_MANAGER_H_

#include "DataManager.hh"
#include "ModuleBase.hh"
#include "PluginHelper.hh"
#include <vector>

using namespace std;

class ModulesManager {
  private:
    CPluginHelper pluginhelper;

    vector<ModuleBase*> modules;

  public:
    void LoadModule();

    void UpdateModule();

    ModulesManager();

    ~ModulesManager();
};

#endif