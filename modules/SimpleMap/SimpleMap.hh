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
    int**  map;
    int**  target;
    int    rubbish_cnt;
    int    gem_cnt;
    bool   only_show_round;
    string map_name;
    string path_name;
    string version;

    SimpleMap();
    SimpleMap(vec_2i map_size);
    ~SimpleMap();
    void         Init();
    void         RandomMap();
    void         CleanMap();
    void         CleanTarget();
    int          GetHash(vec_2i pos);
    virtual bool InMap(vec_2i pos);
    virtual void UpdateSize(vec_2i new_size);
    virtual void LoadMap(const string& load_path);
    virtual void SaveMap(const string& save_path);
    virtual int  GetTarget(vec_2i pos);
    virtual void SetTarget(vec_2i pos, int key);
    virtual int  GetElem(vec_2i pos);
    virtual void SetElem(vec_2i pos, int key);
    int          DoAction(vec_2i start, vec_2i offset);
    int          GetValue(vec_2i pos) { return target[pos.y][pos.x]; }
    int          GetValue4Hash(vec_2i pos);
    inline int*  operator[](int row);
};
#endif