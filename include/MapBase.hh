#pragma once
#ifndef MAP_BASE_H_
#define MAP_BASE_H_

#include "CoreBase.hh"
#include <string>

using namespace std;

enum MapType { MAP_NONE,
               MAP_EDGE,
               MAP_OUT,
               MAP_EMPTY,
               MAP_RUBBISH };

enum PathType { PATH_EMPTY };

class MapBase : public CoreBase {
  public:
    MapBase(){}

    ~MapBase(){}

    virtual int GetElem(vec_2i pos) = 0;

    virtual void SetElem(vec_2i pos, int key) = 0;

    virtual void LoadMap(const string& load_path) = 0;

    virtual void SaveMap(const string& save_path) = 0;
};

#endif
