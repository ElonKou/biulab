#pragma once
#ifndef MAP_EDITOR_BASE_H_
#define MAP_EDITOR_BASE_H_

#include "CoreBase.hh"
#include "MapBase.hh"

enum ToolsType {
    T_NONE,
    T_EDGE,
    T_OUT,
    T_EMPTY,
    T_RUBBISH,
    T_GEM
};
enum SelectionsType {
    S_NONE,
    S_POINT,
    S_LINE,
    S_RECT,
    S_BLOCK,
    S_ALL
};
enum ActionType { A_NONE,
                  A_UNDO,
                  A_REDO };

typedef struct {
    vec_2i         pos[2];
    ToolsType      tool;
    SelectionsType selects;
    ActionType     action;
} HistoryType;

typedef struct MapEditorInfo {
    string name;
    ImVec4 color;
} MapEditorInfo;

class MapEditorBase : public CoreBase {
  public:
    ToolsType                         tools;
    SelectionsType                    selections;
    unordered_map<int, MapEditorInfo> infos;

    MapEditorBase()
        : tools(T_NONE)
        , selections(S_NONE) {
    }

    ~MapEditorBase() {}

    virtual void ModifiedMap(MapBase& mp, vec_2i pos) = 0;
};

#endif
