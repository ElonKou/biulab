#pragma once
#ifndef SIMPLE_MAP_H_
#define SIMPLE_MAP_H_

#include "BiuLabConfig.hh"
#include "MapBase.hh"
#include <string>
#include <vector>

using namespace std;

class SimpleMap : public MapBase {
  private:
    void Print(vec_2i pos);

  public:
    SimpleMap();
    SimpleMap(vec_2i map_size);
    ~SimpleMap();
    int**  map;
    int**  target;
    int    rubbish_cnt;
    int    gem_cnt;
    string map_name;
    string path_name;
    string version;

    void        Init();
    void        RandomMap();
    void        CleanMap();
    void        CleanTarget();
    bool        InMap(vec_2i pos);
    void        UpdateSize(vec_2i new_size);
    void        LoadMap(const string& load_path);
    void        SaveMap(const string& save_path);
    int         GetHash(vec_2i pos);
    int         GetTarget(vec_2i pos);
    void        SetTarget(vec_2i pos, int key);
    int         GetElem(vec_2i pos);
    void        SetElem(vec_2i pos, int key);
    int         DoAction(vec_2i start, vec_2i offset);
    int         GetValue(vec_2i pos) { return target[pos.y][pos.x]; }
    int         GetValue4Hash(vec_2i pos);
    inline int* operator[](int row);
};
#endif