#pragma once
#ifndef LIFE_GAME_WINDOW_HH_
#define LIFE_GAME_WINDOW_HH_

#include "DynamicClass.hh"
// #include "LifeGameController.hh"
// #include "LifeGameControllerWindow.hh"
// #include "LifeGameMapBase.hh"
// #include "LifeGameMapOne.hh"
// #include "LifeGameRuleBase.hh"
// #include "LifeGameRuleOne.hh"
#include "ModuleBase.hh"

// typedef struct LifeGameModuleData {
// LifeGameMapBase*          map_base;
// LifeGameRuleBase*         rule_base;
// LifeGameController*       con;
// LifeGameControllerWindow* con_window;
// } LifeGameModuleData;

class LifeGameModule : public ModuleBase {
  public:
    // LifeGameModuleData* data;

    LifeGameModule();

    ~LifeGameModule();

    virtual void UpdateModule();
};

#endif