#pragma once
#ifndef LIFE_GMAE_RULE_RULE_H_
#define LIFE_GMAE_RULE_RULE_H_

#include "LifeGameRuleBase.hh"
#include <cmath>
#include <iostream>
#include <unordered_map>

using namespace std;

class LifeGameRuleOne : public LifeGameRuleBase {
  public:
    int size;

    LifeGameRuleOne();

    ~LifeGameRuleOne();

    virtual LifeGameElem GetAction(int rule_id, vector<LifeGameElem> values);

    virtual vector<LifeGameElem> GetRule(int rule_id);

    virtual vector<vector<LifeGameElem>> GetRuleList(int rule_id);
};

#endif