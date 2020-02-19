#pragma once
#ifndef MAZE_CONTROLLER_WINDOW_H_
#define MAZE_CONTROLLER_WINDOW_H_

#include "DataManager.hh"
#include "MazeController.hh"
#include "WindowBase.hh"

class MazeControllerWindow : public WindowBase {
  public:
    MazeController* con;

    MazeControllerWindow();

    ~MazeControllerWindow();

    void Show();

    virtual void UpdateData();
};

#endif