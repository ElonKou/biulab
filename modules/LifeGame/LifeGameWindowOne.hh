#pragma once
#ifndef LIFE_GAME_WINDOW_ONE_HH_

#include "WindowBase.hh"

class LifeGameWindowOne : public WindowBase {
  public:
    LifeGameWindowOne();

    ~LifeGameWindowOne();

    virtual void show();
};

#define LIFE_GAME_WINDOW_ONE_HH_
#endif