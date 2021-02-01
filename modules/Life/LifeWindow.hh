#pragma once
#ifndef LIFE_WINDOW_HH_
#define LIFE_WINDOW_HH_

#include "Life.hh"
#include "WindowBase.hh"

class LifeWindow : public WindowBase {
  public:
    Life* life;

    LifeWindow();

    ~LifeWindow();

    virtual void Show();
};

#endif