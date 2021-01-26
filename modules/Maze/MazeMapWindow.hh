#pragma once
#ifndef MAZE_MAP_WINDOW_HH_
#define MAZE_MAP_WINDOW_HH_

#include "MazeMap.hh"
#include "MazePerson.hh"
#include "WindowBase.hh"

class MazeMapWindow : public WindowBase {
  public:
    float       bsize;
    float       padding;
    MazeMap*    maze_map;
    MazePerson* per;

    MazeMapWindow();

    MazeMapWindow(ModulesManager *man);

    ~MazeMapWindow();

    void Show();
};

#endif