/*================================================================
*  Copyright (C)2020 All rights reserved.
*  FileName : MazeController.cc
*  Author   : elonkou
*  Email    : elonkou@ktime.cc
*  Date     : 2020年02月18日 星期二 19时55分13秒
================================================================*/

#include "MazeController.hh"

MazeController::MazeController() {
    speed   = 6;
    running = false;
    stop    = false;
    // 0:for path.
    // 1:for maze object.
    render_target.resize(2);
    render_target[0].p_type = PATH_HISTORY;
    render_target[1].p_type = PATH_ACTOR;
    render_target[1].positions.push_back(per->cur_pos);
}

MazeController::~MazeController() {
}

void MazeController::NextStep() {
    int        dura_frame = 60 / speed;
    static int steps      = 0;
    if (stop) {
        steps = 0;
        render_target[0].positions.clear();
        per->cur_pos = map->start_pos;
        per->forward = per->start_forward;
        stop         = false;
    }
    if (running) {
        steps++;
        if (steps > dura_frame) {
            per->NextStep();
            steps = 0;
            render_target[0].positions.push_back(per->cur_pos);
            if (render_target[0].positions.size() > 300) {
                render_target[0].positions.erase(render_target[0].positions.begin());
            }
        }
    }
    // sender to render
    render_target[1].positions[0] = per->cur_pos;
    map->SetRenderTargets(render_target);
}
