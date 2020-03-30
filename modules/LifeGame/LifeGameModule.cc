/*================================================================
*  Copyright (C)2020 All rights reserved.
*  FileName : LifeGameModule.cc
*  Author   : elonkou
*  Email    : elonkou@ktime.cc
*  Date     : 2020年02月23日 星期日 17时57分35秒
================================================================*/

#include "LifeGameModule.hh"

using namespace std;
DYN_DECLARE(LifeGameModule);

LifeGameModule::LifeGameModule() {
    module_name = "LifeGameModule";
    data        = new LifeGameModuleData();

    data->target.insert({"LifeGameMapBase", false});
    data->target.insert({"LifeGameRuleBase", false});
    data->target.insert({"LifeGameController", false});
    data->target.insert({"LifeGameControllerWindow", false});

    if (!data_manager->HasDataBase("LifeGameMapBase")) {
        data->map_base                  = new LifeGameMapOne();
        data->target["LifeGameMapBase"] = true;
        data_manager->CreateDataBase("MapEditorModule", "LifeGameMapBase", data->map_base);
    }
    if (!data_manager->HasDataBase("LifeGameRuleBase")) {
        data->rule_base                  = new LifeGameRuleOne();
        data->target["LifeGameRuleBase"] = true;
        data_manager->CreateDataBase("MapEditorModule", "LifeGameRuleBase", data->rule_base);
    }
    if (!data_manager->HasDataBase("LifeGameController")) {
        data->con                          = new LifeGameController();
        data->target["LifeGameController"] = true;
        data_manager->CreateDataBase("MapEditorModule", "LifeGameController", data->con);
    }
    if (!data_manager->HasDataBase("LifeGameControllerWindow")) {
        data->con_window                         = new LifeGameControllerWindow();
        data->target["LifeGameControllerWindow"] = true;
        data_manager->CreateDataBase("LifeGameControllerWindow", "LifeGameControllerWindow", data->con_window);
    }
    UpdateData();
}

LifeGameModule::~LifeGameModule() {
}

void LifeGameModule::UpdateModule() {
    if (data->target["LifeGameMapBase"] && show_mapeditor_window) {
        data->map_base->Show();
    }
    if (data->target["LifeGameControllerWindow"]) {
        data->con_window->Show();
    }
}

void LifeGameModule::UpdateData() {
    if (data->target["LifeGameMapBase"]) {
        data->map_base->UpdateData();
    } else {
        data->map_base = GetData<LifeGameMapOne>("LifeGameMapBase", "LifeGameModule");
    }
    if (data->target["LifeGameControllerWindow"]) {
        data->con_window->UpdateData();
    } else {
        data->con_window = GetData<LifeGameControllerWindow>("LifeGameControllerWindow", "LifeGameModule");
    }
}