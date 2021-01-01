/*================================================================
*  Copyright (C)2019 All rights reserved.
*  FileName : RobbieModule.cc
*  Author   : elonkou
*  Email    : elonkou@ktime.cc
*  Date     : 2019年10月05日 星期六 16时33分55秒
================================================================*/

#include "RobbieModule.hh"
#include <iostream>
using namespace std;

DYN_DECLARE(RobbieModule);

RobbieModule::RobbieModule() {
    module_name = "Robbie";
    data        = new RobbieModuleData();

    data->target.insert({"RobbieControl", false});
    data->target.insert({"RobbieControlWindow", false});
    data->target.insert({"SimpleMap", false});
    if (!data_manager->HasDataBase("RobbieControl")) {
        data->controller              = new RobbieController();
        data->target["RobbieControl"] = true;
        data_manager->CreateDataBase("Robbie", "RobbieControl", data->controller);
    }
    if (!data_manager->HasDataBase("RobbieControlWindow")) {
        data->robbie_controll_window        = new RobbieControlWindow();
        data->target["RobbieControlWindow"] = true;
        data_manager->CreateDataBase("Robbie", "RobbieControlWindow", data->robbie_controll_window);
    }
    if (!data_manager->HasDataBase("SimpleMap")) {
        data->dis_map             = new SimpleMap();
        data->target["SimpleMap"] = true;
        data->dis_map->LoadMap(BIULAB_APPLICATION_PATH "/genetic/maps/std.map");
        data_manager->CreateDataBase("Robbie", "SimpleMap", data->dis_map);
    }
}

RobbieModule::~RobbieModule() {}

void RobbieModule::UpdateModule() {
    if (data->robbie_controll_window && data->target["RobbieControlWindow"]) {
        data->robbie_controll_window->Show();
    }
    data->controller->UpdateInFrame();
}
