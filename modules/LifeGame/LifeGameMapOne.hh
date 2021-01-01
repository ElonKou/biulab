#pragma once
#ifndef LIFE_GAME_MAP_ONE_HH_
#define LIFE_GAME_MAP_ONE_HH_

#include "LifeGameMapBase.hh"
#include "LifeGameRuleBase.hh"

class LifeGameMapOne : public LifeGameMapBase {
  public:
    float          bsize;
    float          padding;
    size_t         width;
    size_t         heigth;
    size_t         row; // row number
    LifeGameElem** map;

    LifeGameMapOne();

    ~LifeGameMapOne();

    virtual void Show();

    virtual void UpdateSize(int _width, int _height);

    virtual void RandomElems(int rate = 500);

    virtual void UpdateMap(LifeGameRuleBase& rule, int rule_id);

    virtual vec_2i GetSize();
};

#endif