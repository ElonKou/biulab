#pragma once
#ifndef LIFE_GAME_MAP_ONE_H_
#define LIFE_GAME_MAP_ONE_H_

#include "LifeGameMapBase.hh"
#include "LifeGameRuleBase.hh"

class LifeGameMapOne : public LifeGameMapBase {
  public:
    size_t        size;
    LifeGameElem* map;

    LifeGameMapOne();

    LifeGameMapOne(size_t size_, bool ring_);

    ~LifeGameMapOne();

    virtual void Show();

    virtual void UpdateData();

    virtual void RandomElems(int rate = 50);

    virtual void UpdateMap(LifeGameRuleBase& rule);
};

#endif