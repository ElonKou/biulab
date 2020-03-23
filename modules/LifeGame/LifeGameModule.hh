#pragma once
#ifndef LIFE_GAME_WINDOW_H_
#define LIFE_GAME_WINDOW_H_

#include "DataManager.hh"
#include "DynamicClass.hh"
#include "LifeGameController.hh"
#include "LifeGameControllerWindow.hh"
#include "LifeGameMapBase.hh"
#include "LifeGameRuleBase.hh"
#include "LifeGameRuleOne.hh"
#include "LifeGameRuleTwo.hh"
#include "LifeGameMapOne.hh"
#include "LifeGameMapTwo.hh"
#include "ModuleBase.hh"
#include "WindowBase.hh"
#include <unordered_map>

typedef struct LifeGameModuleData {
    LifeGameMapBase*            map_base;
    LifeGameRuleBase*           rule_base;
    LifeGameController*         con;
    LifeGameControllerWindow*   con_window;
    unordered_map<string, bool> target;
} LifeGameModuleData;

class LifeGameModule : public ModuleBase {
  public:
    LifeGameModuleData* data;

    LifeGameModule();

    ~LifeGameModule();

    virtual void UpdateModule();

    virtual void UpdateData();
};

#endif