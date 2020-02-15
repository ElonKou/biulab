/*================================================================
*  Copyright (C)2019 All rights reserved.
*  FileName : ModulesManager.cc
*  Author   : elonkou
*  Email    : elonkou@ktime.cc
*  Date     : 2019年10月05日 星期六 16时16分46秒
================================================================*/

#include "ModulesManager.hh"
#include <fstream>
#include <iostream>

ModulesManager::ModulesManager() {
    pluginhelper.Load(BIULAB_MODULES_PATH, "*.so");
}

ModulesManager::~ModulesManager() {}

bool ModulesManager::LoadModule(string module_name) {
    ModuleBase* module;
    module = (ModuleBase*)pluginhelper.Create(module_name);
    if (module) {
        PrintSucceed(module->module_name + " load succeed\n");
        modules.push_back(module);
        UpdateData();
        return true;
    } else {
        return false;
    }
}

bool ModulesManager::UnloadModule(string module_name) {
    return true;
}

void ModulesManager::UpdateData() {
    for (size_t i = 0; i < modules.size(); i++) {
        modules[i]->UpdateData();
    }
}

void ModulesManager::UpdateModule() {
    if (module_changed) {
        if (module_selected && !modules_info[module_selected_name]) {
            bool ok = LoadModule(module_selected_name);
            if (ok) {
                modules_info[module_selected_name] = true;
            }
        }
        module_selected = false;
        module_changed  = false;
    }
    for (size_t i = 0; i < modules.size(); i++) {
        modules[i]->UpdateModule();
    }
    // data_manager->Display();
}

void ModulesManager::LoadProgram(vector<string>& program_modules) {
    for (size_t i = 0; i < program_modules.size(); i++) {
        bool ok = LoadModule(program_modules[i]);
        if (ok) {
            modules_info[program_modules[i]] = true;
        }
    }
    for (size_t i = 0; i < modules.size(); i++) {
        modules[i]->UpdateModule();
    }
}

void ModulesManager::GetAllModules() {
    fstream fp;
    string  line;
    fp.open(BIULAB_MODULES_PATH "/ModulesConfig.ini", ios::in);
    while (getline(fp, line)) {
        if (line.size() > 0 && line[0] != ';') {
            if (line[0] != ' ') {
                line.erase(line.begin() + line.size() - 1);
                line += "Module";
                modules_info.insert({line, false});
            }
        }
    }
    fp.close();
}