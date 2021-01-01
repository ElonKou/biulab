#pragma once
#ifndef LIFE_CONTROLLER_WINDOW_HH_
#define LIFE_CONTROLLER_WINDOW_HH_

#include "LifeGameController.hh"
#include "LifeGameMapBase.hh"
#include "WindowBase.hh"

class LifeGameControllerWindow : public WindowBase {
  public:
    LifeGameController* con;

    LifeGameControllerWindow();

    ~LifeGameControllerWindow();

    virtual void Show();

};

#endif