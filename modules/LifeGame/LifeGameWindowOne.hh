#pragma once
#ifndef LIFE_GAME_WINDOW_ONE_H_

#include "WindowBase.hh"

class LifeGameWindowOne : public WindowBase {
  public:
    LifeGameWindowOne();

    ~LifeGameWindowOne();

    virtual void show();

    virtual void UpdateData();
};

#define LIFE_GAME_WINDOW_ONE_H_
#endif