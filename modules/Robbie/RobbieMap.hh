#pragma once
#ifndef ROBBIE_MAP_H_
#define ROBBIE_MAP_H_

#include <string>
#include <vector>
#include "RobbieConfig.hh"
#include "Vec.hh"

using namespace std;

class RobbieMap {
   public:
    RobbieMap();
    RobbieMap(vec_2i map_size);
    ~RobbieMap();
    vec_2i size;
    int **map;
    int **target;
    int **path;
    int rubbish_cnt;
    string map_name;

    vec_2i getSize();
    void randomMap();
    void print(vec_2i pos);
    void drawFrame(PlayActions act, int *gen);
    void cleanTarget();
    bool inMap(vec_2i pos);
    void init();

    void updateSize(vec_2i new_size);

    void loadMap(const string &load_path);
    void saveMap(string &save_path);
    int getHash(vec_2i pos);
    int getTarget(vec_2i pos);
    void setTarget(vec_2i pos, int key);
    int getElem(vec_2i pos);
    void setElem(vec_2i pos, int key);
    int doAction(vec_2i start, vec_2i offset);

    int getValue(vec_2i pos) { return target[pos.y][pos.x]; }
    inline int *operator[](int row);
};
#endif