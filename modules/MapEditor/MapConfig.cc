/*================================================================
*  Copyright (C)2019 All rights reserved.
*  FileName : MapConfig.cc
*  Author   : elonkou
*  Email    : elonkou@ktime.cc
*  Date     : 2019年10月05日 星期六 17时36分47秒
================================================================*/

#include "MapConfig.hh"
#include <iostream>
using namespace std;

bool MapConfig::show_overlay_bar = true;
bool MapConfig::show_control_window = true;
bool MapConfig::show_display_window = true;
bool MapConfig::show_graph_window = false;
bool MapConfig::show_editor_window = true;
bool MapConfig::show_node_window = false;
bool MapConfig::show_inspector_window = true;
MapConfig::MapConfig() {}

MapConfig::~MapConfig() {}