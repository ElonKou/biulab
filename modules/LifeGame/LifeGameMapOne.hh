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
    size_t         index;
    LifeGameElem** map;

    LifeGameMapOne();

    LifeGameMapOne(size_t size_);

    ~LifeGameMapOne();

    virtual void Show();

    virtual void UpdateData();

    virtual void UpdateSize(int width, int height);

    virtual void RandomElems(int rate = 500);

    virtual void UpdateMap(LifeGameRuleBase& rule, int rule_id);

    virtual vec_2i GetSize();
};

#endif