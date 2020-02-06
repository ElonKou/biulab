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
    simple_map = new SimpleMap();
    map_editor = new MapEditor();
    simple_map->init();
    map_editor_window.SetCores(map_editor, simple_map);
    simple_map_window.SetCores(map_editor, simple_map);
    Init();
}

MapEditorModule::~MapEditorModule() {}

void MapEditorModule::UpdateModule() {
    map_editor_window.show();

    simple_map_window.show();

    insepect_window.show();

    overview_window.show();
}

void MapEditorModule::Init() {
    InspectList    lists;
    string         maps_path     = BIULAB_APPLICATION_PATH "/genetic/maps";
    string         robbies_path  = BIULAB_APPLICATION_PATH "/genetic/robbies";
    vector<string> maps_names    = getFiles(maps_path);
    vector<string> robbies_names = getFiles(robbies_path);
    InspectItem    maps_item;
    InspectItem    robbies_item;
    for (size_t i = 0; i < maps_names.size(); i++) {
        vector<string> names = split(maps_names[i], "/");
        maps_item.data.push_back(names[names.size() - 1]);
        maps_item.index     = -1;
        maps_item.selected  = "";
        maps_item.title     = "maps";
        maps_item.collapsed = false;
    }
    for (size_t i = 0; i < robbies_names.size(); i++) {
        vector<string> names = split(robbies_names[i], "/");
        robbies_item.data.push_back(names[names.size() - 1]);
        robbies_item.index     = -1;
        robbies_item.selected  = "";
        robbies_item.title     = "robbies";
        robbies_item.collapsed = false;
    }
    lists.items.push_back(maps_item);
    lists.items.push_back(robbies_item);
    insepect_window.updateInspectItemList(lists);
}