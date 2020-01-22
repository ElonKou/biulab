/*================================================================
*  Copyright (C)2019 All rights reserved.
*  FileName : ModulesManager.cc
*  Author   : elonkou
*  Email    : elonkou@ktime.cc
*  Date     : 2019年10月05日 星期六 16时16分46秒
================================================================*/

#include "ModulesManager.hh"
#include <iostream>

ModulesManager::ModulesManager() {
    data_manager = new DataManager();
}

ModulesManager::~ModulesManager() {}

void ModulesManager::LoadModule() {
    ModuleBase* module;
    pluginhelper.Load(BIULAB_MODULES_PATH, "*.so");

    module = (ModuleBase*)pluginhelper.Create("MapEditorModule");
    module->SetEnvironment(data_manager);
    module->Init();
    modules.push_back(module);
}

void ModulesManager::UpdateModule() {
    for (size_t i = 0; i < modules.size(); i++) {
        modules[i]->UpdateModule();
    }
}
