/*================================================================
*  Copyright (C)2019 All rights reserved.
*  FileName : SimpleMapModule.cc
*  Author   : elonkou
*  Email    : elonkou@ktime.cc
*  Date     : 2019年12月29日 星期日 16时55分05秒
================================================================*/

#include "SimpleMapModule.hh"

using namespace std;

SimpleMapModule::SimpleMapModule() {
    module_name = "SimpleMapModule";
    data        = new SimpleMapData();

    data->target.insert({"SimpleMapWindow", false});
    data->target.insert({"InspectWindow", false});
    data->target.insert({"OverviewWindow", false});
    data->target.insert({"SimpleMap", false});
    data->target.insert({"InspectInfo", false});
    data->target.insert({"OverviewInfo", false});
    if (!data_manager->HasDataBase("SimpleMapWindow")) {
        data->map_window                = new SimpleMapWindow();
        data->target["SimpleMapWindow"] = true;
        data_manager->CreateDataBase("SimpleMapModule", "SimpleMapWindow", data->map_window);
    }
    if (!data_manager->HasDataBase("InspectWindow")) {
        data->insp_window             = new InspectWindow();
        data->target["InspectWindow"] = true;
        data_manager->CreateDataBase("SimpleMapModule", "InspectWindow", data->insp_window);
    }
    if (!data_manager->HasDataBase("OverviewWindow")) {
        data->over_window              = new OverviewWindow();
        data->target["OverviewWindow"] = true;
        data_manager->CreateDataBase("SimpleMapModule", "OverviewWindow", data->over_window);
    }
    if (!data_manager->HasDataBase("SimpleMap")) {
        data->simple_map          = new SimpleMap();
        data->target["SimpleMap"] = true;
        data->simple_map->LoadMap(BIULAB_APPLICATION_PATH "/genetic/maps/std.map");
        data_manager->CreateDataBase("SimpleMapModule", "SimpleMap", data->simple_map);
    }
    if (!data_manager->HasDataBase("InspectInfo")) {
        data->inspect_info          = new InspectInfo();
        data->target["InspectInfo"] = true;
        data_manager->CreateDataBase("SimpleMapModule", "InspectInfo", data->inspect_info);
    }
    if (!data_manager->HasDataBase("OverviewInfo")) {
        data->overview_info          = new OverviewInfo();
        data->target["OverviewInfo"] = true;
        data_manager->CreateDataBase("SimpleMapModule", "OverviewInfo", data->overview_info);
    }
}

SimpleMapModule::~SimpleMapModule() {}

void SimpleMapModule::UpdateModule() {
    if (data->target["SimpleMapWindow"] && show_map_window) {
        data->map_window->Show();
    }
    if (data->target["OverviewWindow"] && show_overlay_window) {
        data->over_window->Show();
    }
    if (data->target["InspectWindow"] && show_inspector_window) {
        data->insp_window->Show();
    }
    Check();
}

void SimpleMapModule::Check() {
    if (data->target["InspectInfo"]) {
        string maps_path    = BIULAB_APPLICATION_PATH "/genetic/maps";
        string robbies_path = BIULAB_APPLICATION_PATH "/genetic/robbies";
        data->inspect_info->AddInfo(robbies_path, "robbies", true);
        data->inspect_info->AddInfo(maps_path, "maps", false);
        if (data->target["OverviewInfo"]) {
            data->inspect_info->UpdateFunc(maps_path);
        }
    }
}