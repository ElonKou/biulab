/*================================================================
*  Copyright (C)2019 All rights reserved.
*  FileName : SimpleMapModule.cc
*  Author   : elonkou
*  Email    : elonkou@ktime.cc
*  Date     : 2019年12月29日 星期日 16时55分05秒
================================================================*/

#include "SimpleMapModule.hh"

using namespace std;

DYN_DECLARE(SimpleMapModule);

SimpleMapModule::SimpleMapModule() {
    module_name = "SimpleMapModule";
    data        = new SimpleMapData();

    if (!data_manager->HasDataBase("SimpleMapWindow")) {
        data->map_window = new SimpleMapWindow();
        data_manager->CreateDataBase("SimpleMapWindow", data->map_window);
    }
    if (!data_manager->HasDataBase("InspectWindow")) {
        data->insp_window = new InspectWindow();
        data_manager->CreateDataBase("InspectWindow", data->insp_window);
    }
    if (!data_manager->HasDataBase("OverviewWindow")) {
        data->over_window = new OverviewWindow();
        data_manager->CreateDataBase("OverviewWindow", data->over_window);
    }
    if (!data_manager->HasDataBase("SimpleMap")) {
        data->simple_map = new SimpleMap();
        data_manager->CreateDataBase("SimpleMap", data->simple_map);
    }
    if (!data_manager->HasDataBase("InspectInfo")) {
        data->inspect_info = new InspectInfo();
        data_manager->CreateDataBase("InspectInfo", data->inspect_info);
    }
    if (!data_manager->HasDataBase("OverviewInfo")) {
        data->overview_info = new OverviewInfo();
        data_manager->CreateDataBase("OverviewInfo", data->overview_info);
    }
    data->simple_map->LoadMap(BIULAB_APPLICATION_PATH "/genetic/maps/std.map");
    data->map_window->UpdateData();
    data->insp_window->UpdateData();
    data->over_window->UpdateData();
    data->inspect_info->UpdateData();
    data->overview_info->UpdateData();
}

SimpleMapModule::~SimpleMapModule() {}

void SimpleMapModule::UpdateModule() {
    data->map_window->Show();
    data->over_window->Show();
    data->insp_window->Show();
    Check();
}

void SimpleMapModule::Check() {
    string maps_path    = BIULAB_APPLICATION_PATH "/genetic/maps";
    string robbies_path = BIULAB_APPLICATION_PATH "/genetic/robbies";
    data->inspect_info->AddInfo(robbies_path, "robbies", true);
    data->inspect_info->AddInfo(maps_path, "maps", false);
    data->inspect_info->UpdateFunc(maps_path);
}