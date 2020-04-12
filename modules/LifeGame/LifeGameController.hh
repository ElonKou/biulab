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

    void UpdateSize(int width, int height);

    void UpdateRule(int rule_id);

    void UpdateRuleMax(int rule_id, int max_height);

    void RandomElems(int rate);

    LifeGameController();

    ~LifeGameController();
};

#endif
