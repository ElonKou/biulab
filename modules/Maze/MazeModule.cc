/*================================================================
*  Copyright (C)2020 All rights reserved.
*  FileName : MazeModule.cc
*  Author   : elonkou
*  Email    : elonkou@ktime.cc
*  Date     : 2020年02月18日 星期二 19时54分44秒
================================================================*/

#include "MazeModule.hh"

DYN_DECLARE(MazeModule);

MazeModule::MazeModule() {
    module_name = "MazeModule";
    data        = new MazeModuleData();

    data->target.insert({"MazePerson", false});
    data->target.insert({"MazeController", false});
    data->target.insert({"MazeControllerWindow", false});
    data->target.insert({"MazeMap", false});
    data->target.insert({"MazeMapWindow", false});
    if (!data_manager->HasDataBase("MazePerson")) {
        data->per                  = new MazePerson();
        data->target["MazePerson"] = true;
        data_manager->CreateDataBase("MazeModule", "MazePerson", data->per);
    }
    if (!data_manager->HasDataBase("MazeController")) {
        data->con                      = new MazeController();
        data->target["MazeController"] = true;
        data_manager->CreateDataBase("MazeModule", "MazeController", data->con);
    }
    if (!data_manager->HasDataBase("MazeControllerWindow")) {
        data->con_window                     = new MazeControllerWindow();
        data->target["MazeControllerWindow"] = true;
        data_manager->CreateDataBase("MazeModule", "MazeControllerWindow", data->con_window);
    }
    if (!data_manager->HasDataBase("MazeMap")) {
        data->map               = new MazeMap();
        data->target["MazeMap"] = true;
        data_manager->CreateDataBase("MazeModule", "MazeMap", data->map);
    }
    if (!data_manager->HasDataBase("MazeMapWindow")) {
        data->map_window              = new MazeMapWindow();
        data->target["MazeMapWindow"] = true;
        data_manager->CreateDataBase("MazeModule", "MazeMapWindow", data->map_window);
    }
}

MazeModule::~MazeModule() {}

void MazeModule::UpdateData() {
    data->con_window->UpdateData();
    data->map_window->UpdateData();
    data->con->UpdateData();
}

void MazeModule::UpdateModule() {
    if (data->target["MazeMapWindow"] && show_simplemap_window) {
        data->map_window->Show();
    }
    if (data->target["MazeControllerWindow"] && show_control_window) {
        data->con_window->Show();
    }
    if (data->target["MazeController"]) {
        data->con->NextStep();
    }
}