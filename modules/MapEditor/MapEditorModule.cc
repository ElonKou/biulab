/*================================================================
*  Copyright (C)2019 All rights reserved.
*  FileName : MapEditorModule.cc
*  Author   : elonkou
*  Email    : elonkou@ktime.cc
*  Date     : 2019年10月05日 星期六 16时34分23秒
================================================================*/

#include "MapEditorModule.hh"

using namespace std;

DYN_DECLARE(MapEditorModule);

MapEditorModule::MapEditorModule() {
    module_name = "MapEditorModule";
    data        = new MapEditorData();

    if (!data_manager->HasDataBase("MapEditorWindow")) {
        data->map_editor_window = new MapEditorWindow();
        data_manager->CreateDataBase("MapEditorWindow", data->map_editor_window);
    }
    if (!data_manager->HasDataBase("SimpleMapWindow")) {
        data->simple_map_window = new SimpleMapWindow();
        data_manager->CreateDataBase("SimpleMapWindow", data->simple_map_window);
    }
    if (!data_manager->HasDataBase("OverviewWindow")) {
        data->overview_window = new OverviewWindow();
        data_manager->CreateDataBase("OverviewWindow", data->overview_window);
    }
    if (!data_manager->HasDataBase("InspectWindow")) {
        data->insepect_window = new InspectWindow();
        data_manager->CreateDataBase("InspectWindow", data->insepect_window);
    }

    if (!data_manager->HasDataBase("SimpleMap")) {
        data->simple_map = new SimpleMap();
        data_manager->CreateDataBase("SimpleMap", data->simple_map);
    }
    if (!data_manager->HasDataBase("MapEditor")) {
        data->map_editor = new MapEditor();
        data_manager->CreateDataBase("MapEditor", data->map_editor);
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
    data->map_editor_window->UpdateData();
    data->simple_map_window->UpdateData();
    data->insepect_window->UpdateData();
    data->overview_window->UpdateData();
    data->overview_info->UpdateData();
    data->inspect_info->UpdateData();
}

MapEditorModule::~MapEditorModule() {}

void MapEditorModule::UpdateModule() {
    data->map_editor_window->Show();
    data->simple_map_window->Show();
    data->insepect_window->Show();
    data->overview_window->Show();
    Check();
}

void MapEditorModule::Check() {
    string maps_path    = BIULAB_APPLICATION_PATH "/genetic/maps";
    string robbies_path = BIULAB_APPLICATION_PATH "/genetic/robbies";
    data->inspect_info->AddInfo(robbies_path, "robbies", true);
    data->inspect_info->AddInfo(maps_path, "maps", false);
    data->inspect_info->UpdateFunc(maps_path);
}