/*================================================================
*  Copyright (C)2019 All rights reserved.
*  FileName : MapEditorModule.cc
*  Author   : elonkou
*  Email    : elonkou@ktime.cc
*  Date     : 2019年10月05日 星期六 16时34分23秒
================================================================*/

#include "MapEditorModule.hh"
#include "DataManager.hh"
#include "DynamicClass.hh"
#include <iostream>

using namespace std;

DYN_DECLARE(MapEditorModule);

MapEditorModule::MapEditorModule() {
    simple_map = new SimpleMap();
    map_editor = new MapEditor();
    simple_map->init();
    map_editor_window.SetCores(map_editor, simple_map);
    simple_map_window.SetCores(map_editor, simple_map);
}

MapEditorModule::~MapEditorModule() {}

void MapEditorModule::UpdateModule() {
    map_editor_window.show();

    // simple_map_window.show();

    // insepect_window.show();

    // overview_window.show();
}

void MapEditorModule::Init() {
    data_manager->CreateDataBase("simple_map", (DataBase*)simple_map);
    data_manager->CreateDataBase("map_editor", (DataBase*)map_editor);
}