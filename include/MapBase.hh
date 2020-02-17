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

enum PathType {
    PATH_ACTOR,
    PATH_HISTORY,
    PATH_PREDICT
};

typedef struct MapElemInfo {
    string name;
    string target;
    ImVec4 color;
} MapElemInfo;

class MapBase : public CoreBase {
  public:
    vec_2i                          size;
    unordered_map<int, MapElemInfo> infos;
    unordered_map<int, MapElemInfo> info_target;
    unordered_map<string, MapType>  elems;
    unordered_map<vec_2i, PathType> render_target;

    MapBase() {
        infos.insert({int(MAP_EDGE), {"Edge", "#", {1.0, 1.0, 1.0, 0.4}}});
        infos.insert({int(MAP_RUBBISH), {"Rubbish", "*", {1.0, 0.0, 0.0, 0.5}}});
        infos.insert({int(MAP_EMPTY), {"Empty", " ", {1.0, 1.0, 1.0, 0.1}}});
        infos.insert({int(MAP_OUT), {"Out", ".", {1.0, 1.0, 1.0, 0.0}}});
        infos.insert({int(MAP_GEM), {"Gem", "$", {0.0, 1.0, 0.0, 0.5}}});
        info_target.insert({int(PATH_ACTOR), {"Actor", " ", {0.6274, 0.1255, 0.9412, 1.0}}});
        info_target.insert({int(PATH_HISTORY), {"History", " ", {0.8471, 0.7490, 0.8471, 1.0}}});
        info_target.insert({int(PATH_PREDICT), {"Predict", " ", {0.7294, 0.3333, 0.8274, 1.0}}});
        elems.insert({"#", MAP_EDGE});
        elems.insert({"*", MAP_RUBBISH});
        elems.insert({" ", MAP_EMPTY});
        elems.insert({".", MAP_OUT});
        elems.insert({"$", MAP_GEM});
    }

    ~MapBase() {}

    virtual bool InMap(vec_2i pos) = 0;

    virtual void UpdateSize(vec_2i new_size) = 0;

    virtual int GetElem(vec_2i pos) = 0;

    virtual void SetElem(vec_2i pos, int key) = 0;

    virtual int GetTarget(vec_2i pos) = 0;

    virtual void SetTarget(vec_2i pos, int key) = 0;

    virtual void LoadMap(const string& load_path) = 0;

    virtual void SaveMap(const string& save_path) = 0;

    void SetRenderTargets(unordered_map<vec_2i, PathType> targets) { render_target = targets; }
};

#endif
