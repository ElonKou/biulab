#pragma once
#ifndef LIFE_GAME_MAP_ONE_H_
#define LIFE_GAME_MAP_ONE_H_

#include "LifeGameMapBase.hh"
#include "LifeGameRuleBase.hh"

class LifeGameMapOne : public LifeGameMapBase {
  public:
    float          bsize;
    float          padding;
    size_t         size;
    size_t         history;
    size_t         index;
    LifeGameElem** map;

    LifeGameMapOne();

    LifeGameMapOne(size_t size_, size_t his_);

    ~LifeGameMapOne();

    virtual void Show();

    virtual void UpdateData();

    virtual void UpdateSize(int width, int history);

    virtual void RandomElems(int rate = 50);

    virtual void UpdateMap(LifeGameRuleBase& rule, int rule_id);
};

#endif