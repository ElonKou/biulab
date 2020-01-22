#pragma once
#ifndef SIMPLE_MAP_H_
#define SIMPLE_MAP_H_

#include "BiuLabTypes.hh"
#include "DataBase.hh"
#include "MapBase.hh"
#include <string>
#include <vector>

using namespace std;

class SimpleMap : public DataBase {
  private:
    void print(vec_2i pos);
    void cleanTarget();

  public:
    SimpleMap();
    SimpleMap(vec_2i map_size);
    ~SimpleMap();
    vec_2i size;
    int**  map;
    int**  target;
    int    rubbish_cnt;
    string map_name;
    string path_name;

    void         init();
    void         RandomMap();
    void         ClearMap();
    bool         inMap(vec_2i pos);
    void         updateSize(vec_2i new_size);
    void         loadMap(const string& load_path);
    void         saveMap(const string& save_path);
    int          getHash(vec_2i pos);
    int          getTarget(vec_2i pos);
    void         setTarget(vec_2i pos, int key);
    virtual int  getElem(vec_2i pos);
    virtual void setElem(vec_2i pos, int key);
    int          doAction(vec_2i start, vec_2i offset);
    int          getValue(vec_2i pos) { return target[pos.y][pos.x]; }
    inline int*  operator[](int row);
};
#endif