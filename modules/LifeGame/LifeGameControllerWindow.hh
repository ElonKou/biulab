#pragma once
#ifndef LIFE_CONTROLLER_WINDOW_H_
#define LIFE_CONTROLLER_WINDOW_H_

#include "DataManager.hh"
#include "LifeGameController.hh"
#include "LifeGameMapBase.hh"
#include "WindowBase.hh"

class LifeGameControllerWindow : public WindowBase {
  public:
    LifeGameController* con;

    LifeGameControllerWindow();

    ~LifeGameControllerWindow();

    virtual void Show();

    virtual void UpdateData();
};

#endif