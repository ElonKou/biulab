#pragma once
#ifndef LIFE_GAME_RULE_BASE_H_
#define LIFE_GAME_RULE_BASE_H_

#include "CoreBase.hh"
#include "Lib.hh"
#include "LifeGameConfig.hh"
#include <vector>

using namespace std;

class LifeGameRuleBase : public CoreBase {
  public:
    LifeGameRuleBase() {}

    ~LifeGameRuleBase() {}

    virtual LifeGameElem GetAction(int rule_id, vector<LifeGameElem> values) = 0;

    virtual vector<LifeGameElem> GetRule(int rule_id) = 0;

    virtual vector<vector<LifeGameElem>> GetRuleList(int rule_id) = 0;
};

#endif