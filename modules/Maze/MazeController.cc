/*================================================================
*  Copyright (C)2020 All rights reserved.
*  FileName : MazeController.cc
*  Author   : elonkou
*  Email    : elonkou@ktime.cc
*  Date     : 2020年02月18日 星期二 19时55分13秒
================================================================*/

#include "MazeController.hh"

MazeController::MazeController() {
    running = false;
    stop    = false;
    speed   = 6;
}

MazeController::~MazeController() {
}

void MazeController::NextStep() {
    vector<TargetElem> render_target;
    TargetElem         maze_per;

    // Core code
    static int step_all = 0;
    int        dura     = 60 / speed;
    if (stop) {
        step_all = 0;
        paths.positions.clear();
        per->cur_pos = map->start_pos;
        per->forward = per->start_forward;
        stop         = false;
    }
    if (running) {
        step_all++;
        if (step_all > dura && (!map->CheckExit(per->cur_pos))) {
            per->NextStep();
            step_all = 0;
            paths.positions.push_back(per->cur_pos);
            if (paths.positions.size() > 300) {
                paths.positions.erase(paths.positions.begin());
            }
        }
    }
    // End core

    paths.p_type    = PATH_HISTORY;
    maze_per.p_type = PATH_ACTOR;
    maze_per.positions.push_back(per->cur_pos);
    render_target.push_back(paths);
    render_target.push_back(maze_per);
    map->SetRenderTargets(render_target);
}

void MazeController::UpdateData() {
    vec_2i start_pos = vec_2i(6, 3);
    vec_2i end_pos   = vec_2i(9, 6);
    map              = GetData<MazeMap>("MazeMap", "MazeController");
    per              = GetData<MazePerson>("MazePerson", "MazeController");
    map->LoadMap(BIULAB_APPLICATION_PATH "/genetic/maps/high.map");
    map->UpdateMazeMap();
    map->SetStartPos(start_pos);
    map->SetEndPos(end_pos);
    per->maze_map      = map;
    per->cur_pos       = start_pos;
    per->start_forward = DIR_DOWN;
    per->forward       = per->start_forward;
}