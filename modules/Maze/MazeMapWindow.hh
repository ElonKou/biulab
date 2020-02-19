#pragma once
#ifndef MAZE_MAP_WINDOW_H_
#define MAZE_MAP_WINDOW_H_

#include "DataManager.hh"
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

    ~MazeMapWindow();

    void Show();

    virtual void UpdateData();
};

#endif