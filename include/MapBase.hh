#pragma once
#ifndef MAP_BASE_H_
#define MAP_BASE_H_

#include "CoreBase.hh"
#include <string>
#include <unordered_map>

using namespace std;

enum MapType {
    MAP_EDGE,
    MAP_RUBBISH,
    MAP_EMPTY,
    MAP_OUT,
    MAP_GEM
};

enum PathType { PATH_EMPTY };

typedef struct MapElemInfo {
    MapType type;
    string  name;
    string  target;
    ImVec4  color;
} MapElemInfo;

class MapBase : public CoreBase {
  public:
    unordered_map<int, MapElemInfo> infos;
    unordered_map<string, MapType>  elems;

    MapBase() {
        infos.insert({int(MAP_EDGE), {MAP_EDGE, "Edge", "#", {1.0, 1.0, 1.0, 0.4}}});
        infos.insert({int(MAP_RUBBISH), {MAP_RUBBISH, "Rubbish", "*", {1.0, 0.0, 0.0, 0.5}}});
        infos.insert({int(MAP_EMPTY), {MAP_EMPTY, "Empty", " ", {1.0, 1.0, 1.0, 0.1}}});
        infos.insert({int(MAP_OUT), {MAP_OUT, "Out", ".", {1.0, 1.0, 1.0, 0.0}}});
        infos.insert({int(MAP_GEM), {MAP_GEM, "Gem", "$", {0.0, 1.0, 0.0, 0.5}}});
        elems.insert({"#", MAP_EDGE});
        elems.insert({"*", MAP_RUBBISH});
        elems.insert({" ", MAP_EMPTY});
        elems.insert({".", MAP_OUT});
        elems.insert({"$", MAP_GEM});
    }

    ~MapBase() {}

    virtual int GetElem(vec_2i pos) = 0;

    virtual void SetElem(vec_2i pos, int key) = 0;

    virtual void LoadMap(const string& load_path) = 0;

    virtual void SaveMap(const string& save_path) = 0;
};

#endif
