#pragma once
#ifndef LIFE_2D_CONTROLLER_HH_
#define LIFE_2D_CONTROLLER_HH_

#include "Life.hh"
#include "WindowBase.hh"

class LifeController : public WindowBase {
  public:
    Life* life;

    LifeController();

    ~LifeController();

    virtual void Show();
};

#endif