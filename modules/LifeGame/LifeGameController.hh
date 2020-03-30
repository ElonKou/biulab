#pragma once
#ifndef LIFE_GAME_CONTROLLER_H_
#define LIFE_GAME_CONTROLLER_H_

#include "CoreBase.hh"
#include "LifeGameMapBase.hh"
#include "LifeGameRuleBase.hh"

class LifeGameController : public CoreBase {
  public:
    LifeGameMapBase* map_base;

    LifeGameRuleBase* rule_base;

    void UpdateSize(int width, int history);

    void UpdateRule(int rule_id);

    void RandomElems(int rate);

    LifeGameController();

    ~LifeGameController();
};

#endif
