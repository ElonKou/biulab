#pragma once
#ifndef LIFE_GAME_CONFIG_HH_
#define LIFE_GAME_CONFIG_HH_

#include <iostream>

#define LIFE_GAME_DIM_MAX 1024   // max of DIM
#define LIFE_GAME_DIM_WIDTH 160  // DIM width
#define LIFE_GAME_DIM_HEIGHT 160 // DIM width
#define ELEM_ONE_SIZE 2
#define ELEM_ONE_RANGE 3
#define ELEM_TWO_SIZE 2
#define ELEM_TWO_RANGE 9

typedef enum {
    ElemDead  = 0,
    ElemAlive = 1
} LifeGameElem;

#endif