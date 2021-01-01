#pragma once
#ifndef MAP_BASE_HH_
#define MAP_BASE_HH_

#include "CoreBase.hh"
#include <string>
#include <unordered_map>

using namespace std;

enum MapType {
    MAP_EDGE,
    MAP_RUBBISH,
    MAP_EMPTY,
    MAP_OUT,
    MAP_GEM,
    MAP_MAZE,
    MAP_DOOR,
    MAP_FLAG
};

enum PathType {
    PATH_ACTOR,
    PATH_HISTORY,
    PATH_PREDICT,
};

typedef struct MapElemInfo {
    string name;
    string target;
    ImVec4 color;
} MapElemInfo;

typedef struct TargetElem {
    PathType       p_type;
    vector<vec_2i> positions;
} TargetElem;

static unordered_map<string, ImVec4> map_color = {
    {"None", {0.0, 0.0, 0.0, 1.0}},
    {"Edge", {1.0, 1.0, 1.0, 0.4}},
    {"Rubbish", {1.0, 0.0, 0.0, 0.5}},
    {"Empty", {1.0, 1.0, 1.0, 0.1}},
    {"Out", {1.0, 1.0, 1.0, 0.0}},
    {"Gem", {0.0, 0.78, 0.55, 1.0}},
    {"Maze", {1.0, 0.0, 1.0, 1.0}},
    {"Door", {1.0, 0.0, 1.0, 1.0}},
    {"Flag", {1.0, 0.0, 0.0, 1.0}},
    {"Actor", {1.0, 0.8431, 0.0, 0.8}},
    {"History", {1.0, 0.8431, 0.0, 0.2}},
    {"Predict", {0.7294, 0.3333, 0.8274, 1.0}},
};

class MapBase : public CoreBase {
  public:
    vec_2i size;
    unordered_map<int, MapElemInfo> infos;
    unordered_map<int, MapElemInfo> info_target;
    unordered_map<string, MapType>  elems;
    vector<TargetElem> render_target;

    MapBase() {
        infos.insert({int(MAP_EDGE), {"Edge", "#", map_color["Edge"]}});
        infos.insert({int(MAP_RUBBISH), {"Rubbish", "*", map_color["Rubbish"]}});
        infos.insert({int(MAP_EMPTY), {"Empty", " ", map_color["Empty"]}});
        infos.insert({int(MAP_OUT), {"Out", ".", map_color["Out"]}});
        infos.insert({int(MAP_GEM), {"Gem", "$", map_color["Gem"]}});
        infos.insert({int(MAP_MAZE), {"Maze", "+", map_color["Maze"]}});
        infos.insert({int(MAP_DOOR), {"Door", "p", map_color["Door"]}});
        infos.insert({int(MAP_FLAG), {"Flag", "p", map_color["Flag"]}});
        info_target.insert({int(PATH_ACTOR), {"Actor", " ", map_color["Actor"]}});
        info_target.insert({int(PATH_HISTORY), {"History", " ", map_color["History"]}});
        info_target.insert({int(PATH_PREDICT), {"Predict", " ", map_color["Predict"]}});
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

    void SetRenderTargets(vector<TargetElem>& targets) { render_target = targets; }
};

#endif
