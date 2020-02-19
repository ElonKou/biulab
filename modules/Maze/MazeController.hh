#pragma once
#ifndef MAZE_CONTROLLER_H_
#define MAZE_CONTROLLER_H_

#include "CoreBase.hh"
#include "DataManager.hh"
#include "MazeMap.hh"
#include "MazePerson.hh"

class MazeController : public CoreBase {
  public:
    bool        running;
    bool        stop;
    int         speed;
    TargetElem  paths;
    MazePerson* per;
    MazeMap*    map;

    MazeController();

    ~MazeController();

    void NextStep();

    void UpdateData();
};

#endif