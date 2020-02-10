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

    data->target.insert({"MapEditorWindow", false});
    data->target.insert({"SimpleMapWindow", false});
    data->target.insert({"OverviewWindow", false});
    data->target.insert({"InspectWindow", false});
    data->target.insert({"SimpleMap", false});
    data->target.insert({"MapEditor", false});
    data->target.insert({"InspectInfo", false});
    data->target.insert({"OverviewInfo", false});
    if (!data_manager->HasDataBase("MapEditorWindow")) {
        data->map_editor_window = new MapEditorWindow();
        data_manager->CreateDataBase("MapEditorModule", "MapEditorWindow", data->map_editor_window);
        data->target["MapEditorWindow"] = true;
    }
    if (!data_manager->HasDataBase("SimpleMapWindow")) {
        data->simple_map_window = new SimpleMapWindow();
        data_manager->CreateDataBase("MapEditorModule", "SimpleMapWindow", data->simple_map_window);
        data->target["SimpleMapWindow"] = true;
    }
    if (!data_manager->HasDataBase("OverviewWindow")) {
        data->overview_window = new OverviewWindow();
        data_manager->CreateDataBase("MapEditorModule", "OverviewWindow", data->overview_window);
        data->target["OverviewWindow"] = true;
    }
    if (!data_manager->HasDataBase("InspectWindow")) {
        data->insepect_window = new InspectWindow();
        data_manager->CreateDataBase("MapEditorModule", "InspectWindow", data->insepect_window);
        data->target["InspectWindow"] = true;
    }

    if (!data_manager->HasDataBase("SimpleMap")) {
        data->simple_map = new SimpleMap();
        data_manager->CreateDataBase("MapEditorModule", "SimpleMap", data->simple_map);
        data->target["SimpleMap"] = true;
    }
    if (!data_manager->HasDataBase("MapEditor")) {
        data->map_editor = new MapEditor();
        data_manager->CreateDataBase("MapEditorModule", "MapEditor", data->map_editor);
        data->target["MapEditor"] = true;
    }
    if (!data_manager->HasDataBase("InspectInfo")) {
        data->inspect_info = new InspectInfo();
        data_manager->CreateDataBase("MapEditorModule", "InspectInfo", data->inspect_info);
        data->target["InspectInfo"] = true;
    }
    if (!data_manager->HasDataBase("OverviewInfo")) {
        data->overview_info = new OverviewInfo();
        data_manager->CreateDataBase("MapEditorModule", "OverviewInfo", data->overview_info);
        data->target["OverviewInfo"] = true;
    }
    UpdateData();
}

MapEditorModule::~MapEditorModule() {}

void MapEditorModule::UpdateModule() {
    if (data->target["MapEditorWindow"] && show_mapeditor_window) {
        data->map_editor_window->Show();
    }
    if (data->target["SimpleMapWindow"] && show_simplemap_window) {
        data->simple_map_window->Show();
    }
    if (data->target["InspectWindow"] && show_inspector_window) {
        data->insepect_window->Show();
    }
    if (data->target["OverviewWindow"] && show_overlay_window) {
        data->overview_window->Show();
    }
    Check();
}

void MapEditorModule::UpdateData() {
    if (data->target["MapEditorWindow"]) {
        data->map_editor_window->UpdateData();
    } else {
        data->map_editor_window = GetData<MapEditorWindow>("MapEditorWindow", "MapEditorModule");
    }
    if (data->target["SimpleMapWindow"]) {
        data->simple_map_window->UpdateData();
    } else {
        data->simple_map_window = GetData<SimpleMapWindow>("SimpleMapWindow", "MapEditorModule");
    }
    if (data->target["InspectWindow"]) {
        data->insepect_window->UpdateData();
    } else {
        data->insepect_window = GetData<InspectWindow>("InspectWindow", "MapEditorModule");
    }
    if (data->target["OverviewWindow"]) {
        data->overview_window->UpdateData();
    } else {
        data->overview_window = GetData<OverviewWindow>("OverviewWindow", "MapEditorModule");
    }
    if (data->target["SimpleMap"]) {
        data->simple_map->LoadMap(BIULAB_APPLICATION_PATH "/genetic/maps/std.map");
    } else {
        data->simple_map = GetData<SimpleMap>("SimpleMap", "MapEditorModule");
    }
    if (data->target["InspectInfo"]) {
        data->inspect_info->UpdateData();
    } else {
        data->inspect_info = GetData<InspectInfo>("InspectInfo", "MapEditorModule");
    }
    if (data->target["OverviewInfo"]) {
        data->overview_info->UpdateData();
    } else {
        data->overview_info = GetData<OverviewInfo>("OverviewInfo", "MapEditorModule");
    }
    data->inspect_info->UpdateData();
}

void MapEditorModule::Check() {
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