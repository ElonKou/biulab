#pragma once
#ifndef LIFE_GAME_WINDOW_TWO_H_
#define LIFE_GAME_WINDOW_TWO_H_

#include "WindowBase.hh"

class LifeGameWindowTwo : public WindowBase {
  public:
    LifeGameWindowTwo();

    ~LifeGameWindowTwo();

    virtual void show();

    virtual void UpdateData();
};

#endif