#pragma once
#ifndef LIFE_GAME_CONFIG_H_
#define LIFE_GAME_CONFIG_H_

#include <iostream>

#define LIFE_GAME_DIM_WIDTH 128
#define LIFE_GAME_DIM_HEIGT 96
#define ELEM_ONE_SIZE 2
#define ELEM_ONE_RANGE 3
#define ELEM_TWO_SIZE 2
#define ELEM_TWO_RANGE 9

typedef enum {
    ElemDead  = 0,
    ElemAlive = 1
} LifeGameElem;

#endif