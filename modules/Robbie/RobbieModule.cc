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

    // data->target.insert({"RobbieControl", false});
    // data->target.insert({"RobbieControlWindow", false});
    // data->target.insert({"SimpleMap", false});
    // if (!data_manager->HasDataBase("RobbieControl")) {
    //     data->controller              = new RobbieController();
    //     data->target["RobbieControl"] = true;
    //     data_manager->CreateDataBase("Robbie", "RobbieControl", data->controller);
    // }
    // if (!data_manager->HasDataBase("RobbieControlWindow")) {
    //     data->robbie_controll_window        = new RobbieControlWindow();
    //     data->target["RobbieControlWindow"] = true;
    //     data_manager->CreateDataBase("Robbie", "RobbieControlWindow", data->robbie_controll_window);
    // }
    // if (!data_manager->HasDataBase("SimpleMap")) {
    //     data->dis_map             = new SimpleMap();
    //     data->target["SimpleMap"] = true;
    //     data->dis_map->LoadMap(BIULAB_APPLICATION_PATH "/genetic/maps/std.map");
    //     data_manager->CreateDataBase("Robbie", "SimpleMap", data->dis_map);
    // }
}

RobbieModule::~RobbieModule() {}

void RobbieModule::InitModule() {
    data             = new RobbieModuleData();
    data->controller = new RobbieController();
    data->rc_window  = new RobbieControlWindow(manager);
    data->dis_map    = new SimpleMap();
    data->map_window = new SimpleMapWindow(manager);
    data->isp_window = new InspectWindow(manager);
    data->isp_info   = new InspectInfo();

    data->dis_map->LoadMap(BIULAB_APPLICATION_PATH "/genetic/maps/std.map");
    data->rc_window->robbie_controll   = data->controller;
    data->controller->data->dis_map    = data->dis_map;
    data->map_window->simple_map       = data->dis_map;
    data->isp_window->info             = data->isp_info;
    data->isp_window->info->simple_map = data->dis_map;
}

void RobbieModule::UpdateModule() {
    if (data->rc_window && manager->options.show_control_window) {
        data->rc_window->Show();
    }
    if (data->dis_map && manager->options.show_map_window) {
        data->map_window->Show();
    }
    if (data->isp_window && manager->options.show_inspector_window) {
        data->isp_window->Show();
    }
    data->controller->UpdateInFrame();
    string maps_path    = BIULAB_APPLICATION_PATH "/genetic/maps";
    string robbies_path = BIULAB_APPLICATION_PATH "/genetic/robbies";
    data->isp_info->AddInfo(robbies_path, "robbies", true);
    data->isp_info->AddInfo(maps_path, "maps", false);
    data->isp_info->UpdateFunc(maps_path);
}
