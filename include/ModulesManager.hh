#pragma once
#ifndef MODULES_MANAGER_H_
#define MODULES_MANAGER_H_

#include <vector>
#include "ModuleBase.hh"
#include "PluginHelper.hh"

using namespace std;

class ModulesManager {
   private:
    CPluginHelper pluginhelper;

    vector<ModuleBase *> modules;

   public:
    void LoadModule();

    void UpdateModule();

    ModulesManager();

    ~ModulesManager();
};

#endif