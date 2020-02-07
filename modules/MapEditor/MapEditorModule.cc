/*================================================================
*  Copyright (C)2019 All rights reserved.
*  FileName : MapEditorModule.cc
*  Author   : elonkou
*  Email    : elonkou@ktime.cc
*  Date     : 2019年10月05日 星期六 16时34分23秒
================================================================*/

#include "MapEditorModule.hh"
#include "DynamicClass.hh"

using namespace std;

DYN_DECLARE(MapEditorModule);

MapEditorModule::MapEditorModule() {
    module_name = "MapEditorModule";
    data                = new MapEditorData();
    data->simple_map    = new SimpleMap();
    data->map_editor    = new MapEditor();
    data->inspect_info  = new InspectInfo();
    data->overview_info = new OverviewInfo();
    data->simple_map->LoadMap(BIULAB_APPLICATION_PATH "/genetic/maps/std.map");
    data_manager->CreateDataBase("SimpleMap", data->simple_map);
    data_manager->CreateDataBase("MapEditor", data->map_editor);
    data_manager->CreateDataBase("InspectInfo", data->inspect_info);
    data_manager->CreateDataBase("OverviewInfo", data->overview_info);
    map_editor_window.UpdateData();
    simple_map_window.UpdateData();
    insepect_window.UpdateData();
    overview_window.UpdateData();
}

MapEditorModule::~MapEditorModule() {}

void MapEditorModule::UpdateModule() {
    map_editor_window.Show();
    simple_map_window.Show();
    insepect_window.Show();
    overview_window.Show();
    Check();
}

void MapEditorModule::Check() {
    string         maps_path     = BIULAB_APPLICATION_PATH "/genetic/maps";
    string         robbies_path  = BIULAB_APPLICATION_PATH "/genetic/robbies";
    vector<string> maps_names    = GetFiles(maps_path);
    vector<string> robbies_names = GetFiles(robbies_path);
    InspectItem    maps_item;
    InspectItem    robbies_item;
    for (size_t i = 0; i < maps_names.size(); i++) {
        vector<string> names = Split(maps_names[i], "/");
        maps_item.data.push_back(names[names.size() - 1]);
        maps_item.selected  = "";
        maps_item.title     = "maps";
        maps_item.collapsed = false;
    }
    for (size_t i = 0; i < robbies_names.size(); i++) {
        vector<string> names = Split(robbies_names[i], "/");
        robbies_item.data.push_back(names[names.size() - 1]);
        robbies_item.selected  = "";
        robbies_item.title     = "robbies";
        robbies_item.collapsed = true;
    }
    data->inspect_info->items.insert({"robbies", robbies_item});
    data->inspect_info->items.insert({"maps", maps_item});
    if (data->overview_info->items.size() == 0) {
        OverviewInfoItem over_item;
        over_item.data.insert({"maps", data->inspect_info->items["maps"].selected});
        data->overview_info->items.insert({"simplemap", over_item});
    } else {
        data->overview_info->items["simplemap"].data["maps"] = data->inspect_info->items["maps"].selected;
    }
    if (data->inspect_info->items.size() > 0 && data->inspect_info->items["maps"].changed) {
        string map_name_                          = data->inspect_info->items["maps"].selected;
        data->inspect_info->items["maps"].changed = false;
        data->simple_map->LoadMap(maps_path + "/" + map_name_);
        map_editor_window.UpdateData();
    }
}