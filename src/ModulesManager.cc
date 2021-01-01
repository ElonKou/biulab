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
    module = NULL;
    pluginhelper.Load(BIULAB_MODULES_PATH, "*.so");
}

ModulesManager::~ModulesManager() {
}

bool ModulesManager::LoadModule(string module_name) {
    std::cout << module_name;
    module = (ModuleBase*)pluginhelper.Create(module_name);
    std::cout << ":" << module << std::endl;
    if (module) {
        PrintSucceed(module->module_name + " load succeed\n");
    } else {
        PrintError(module->module_name + " load Failed\n");
    }
    for (size_t i = 0; i < modules_info.size(); i++) {
        if (modules_info[i].module_name == module_name) {
            modules_info[i].running = true;
        } else {
            modules_info[i].running = false;
        }
    }
    return (module == NULL);
}

bool ModulesManager::UnloadModule(string module_name) {
    return true;
}

bool ModulesManager::QuitModule() {
    if (module) {
        module = NULL;
        for (size_t i = 0; i < modules_info.size(); i++) {
            modules_info[i].running = false;
        }
    }
    return true;
}

void ModulesManager::UpdateModule() {
    if (module) {
        module->UpdateModule();
    }
}

void ModulesManager::GetAllModules() {
    fstream fp;
    string  line;
    fp.open(BIULAB_MODULES_PATH "/ModulesConfig.ini", ios::in);
    while (getline(fp, line)) {
        ModuleInfoData elem;
        if (line.size() > 0 && line[0] != ';' && line[0] != ' ') {
            elem.running     = false;
            elem.module_name = Split(line, ":")[0] + "Module";
            getline(fp, line);
            elem.module_info = Split(line, ":")[1];
            getline(fp, line);
            elem.module_icon = Split(line, ":")[1];
            getline(fp, line);
            elem.module_share = Split(line, ":")[1];
            // load icon image.
            int    width     = 0;
            int    height    = 0;
            string icon_path = BIULAB_INSTALL_PATH "/resources/icons/" + elem.module_icon;
            bool   ret       = LoadTextureFromFile(icon_path.c_str(), &elem.icon_id, &width, &height);
            elem.icon_size   = ImVec2(width, height);
            if (!ret) {
                std::cout << "Load icon failed" << std::endl;
            }
            modules_info.push_back(elem);
        }
    }
    fp.close();
}