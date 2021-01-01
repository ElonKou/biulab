#pragma once
#ifndef LIFE_GAME_WINDOW_TWO_HH_
#define LIFE_GAME_WINDOW_TWO_HH_

#include "WindowBase.hh"

class LifeGameWindowTwo : public WindowBase {
  public:
    LifeGameWindowTwo();

    ~LifeGameWindowTwo();

    virtual void show();
};

#endif