/*================================================================
*  Copyright (C)2019 All rights reserved.
*  FileName : MapEditorModule.cc
*  Author   : elonkou
*  Email    : elonkou@ktime.cc
*  Date     : 2019年10月05日 星期六 16时34分23秒
================================================================*/

#include "MapEditorModule.hh"
#include <iostream>
#include "DynamicClass.hh"

using namespace std;

DYN_DECLARE(MapEditorModule);

MapEditorModule::MapEditorModule() {}

MapEditorModule::~MapEditorModule() {}

void MapEditorModule::UpdateModule() {
    map_editor_window.show();

    simple_map_window.show();

    insepect_window.show();

    overview_window.show();
}