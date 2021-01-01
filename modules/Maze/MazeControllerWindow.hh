#pragma once
#ifndef MAZE_CONTROLLER_WINDOW_HH_
#define MAZE_CONTROLLER_WINDOW_HH_

#include "MazeController.hh"
#include "WindowBase.hh"

class MazeControllerWindow : public WindowBase {
  public:
    MazeController* con;

    MazeControllerWindow();

    ~MazeControllerWindow();

    void Show();
};

#endif