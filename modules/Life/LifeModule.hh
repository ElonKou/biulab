#pragma once
#ifndef LIFE_GAME_2D_HH_
#define LIFE_GAME_2D_HH_

#include "DynamicClass.hh"
#include "LifeController.hh"
#include "LifeWindow.hh"
#include "ModuleBase.hh"

class LifeModule : public ModuleBase {
  public:
    Life*           life;
    LifeWindow*     window;
    LifeController* con;

    LifeModule();

    ~LifeModule();

    virtual void InitModule();

    virtual void UpdateModule();
};

#endif
