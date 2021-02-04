#pragma once
#ifndef LIFE_2D_HH_
#define LIFE_2D_HH_

class Life {
  public:
    bool  run; // default false
    int   fps; // 1/fps
    int** map;
    int** temp;
    int   width;
    int   height;

    Life();

    ~Life();

    int Role23(int i, int j);

    void UpdateFrame();
};

#endif