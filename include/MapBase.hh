#pragma once
#ifndef MAP_BASE_H_
#define MAP_BASE_H_

#include "BiuLabTypes.hh"
#include <string>

using namespace std;

enum MapType { MAP_NONE,
               MAP_EDGE,
               MAP_OUT,
               MAP_EMPTY,
               MAP_RUBBISH };

enum PathType { PATH_EMPTY };

class MapBase {
  public:
    MapBase();

    ~MapBase();

    virtual int getElem(vec_2i pos) = 0;

    virtual void setElem(vec_2i pos, int key) = 0;

    virtual void loadMap(const string& load_path) = 0;

    virtual void saveMap(const string& save_path) = 0;
};

#endif
