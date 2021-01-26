#pragma once
#ifndef MAZE_CONTROLLER_HH_
#define MAZE_CONTROLLER_HH_

#include "CoreBase.hh"
#include "MazeMap.hh"
#include "MazePerson.hh"

class MazeController : public CoreBase {

  public:
    bool               running;
    bool               stop;
    int                speed;
    MazePerson*        per;
    MazeMap*           map;
    vector<TargetElem> render_target;

    MazeController();

    MazeController(MazePerson *p);

    ~MazeController();

    void NextStep();
};

#endif