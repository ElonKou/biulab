/*================================================================
*  Copyright (C)2020 All rights reserved.
*  FileName : MazeModule.cc
*  Author   : elonkou
*  Email    : elonkou@ktime.cc
*  Date     : 2020年02月18日 星期二 19时54分44秒
================================================================*/

#include "MazeModule.hh"

DYN_DECLARE(MazeModule);

MazeModule::MazeModule() {
    module_name = "MazeModule";
}

MazeModule::~MazeModule() {
}

void MazeModule::InitModule() {
    data             = new MazeModuleData();
    data->per        = new MazePerson();
    data->con        = new MazeController(data->per);
    data->con_window = new MazeControllerWindow(manager);
    data->map        = new MazeMap();
    data->map_window = new MazeMapWindow(manager);

    vec_2i start_pos   = vec_2i(6, 3);
    vec_2i end_pos     = vec_2i(11, 7);
    data->per->cur_pos = start_pos;
    data->map->LoadMap(BIULAB_APPLICATION_PATH "/genetic/maps/high.map");
    data->map->UpdateMazeMap();
    data->map->SetStartPos(start_pos);
    data->map->SetEndPos(end_pos);

    data->con->map             = data->map;
    data->con_window->con      = data->con;
    data->map_window->maze_map = data->map;
    data->map_window->per      = data->per;
    data->per->map             = data->map;
}

void MazeModule::UpdateModule() {
    if (data->map_window) {
        data->map_window->Show();
    }
    if (data->con_window) {
        data->con_window->Show();
    }
    if (data->con) {
        data->con->NextStep();
    }
}