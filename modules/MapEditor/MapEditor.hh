#pragma once
#ifndef EDITOR_MAP_H_
#define EDITOR_MAP_H_

#include "BiuLabTypes.hh"
#include "Lib.hh"
#include "SimpleMap.hh"
#include "SimpleMapConfig.hh"

enum ToolsType {
    T_NONE,
    T_EDGE,
    T_OUT,
    T_EMPTY,
    T_RUBBISH
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

class MapEditor : public CoreBase {
  private:
    int         selectPosCnt;
    vec_2i      selectPos[2];
    HistoryType histories[10];

  public:
    int width;
    int height;

    ToolsType                            tools;
    SelectionsType                       selections;
    unordered_map<string, MapEditorInfo> infos;

    MapEditor();
    ~MapEditor();
    void CheckAndSetElem(SimpleMap& mp, vec_2i pos);

    void DrawLine(SimpleMap& mp, vec_2i pos_x, vec_2i pos_y);
    void DrawRect(SimpleMap& mp, vec_2i pos_x, vec_2i pos_y);
    void DrawPoint(SimpleMap& mp, vec_2i pos);
    void DrawBlock(SimpleMap& mp, vec_2i pos);
    void DrawAll(SimpleMap& mp, vec_2i pos);

    void UpdateMap(SimpleMap& mp);
    void SetTools(ToolsType tool);
    void SetSelection(SelectionsType slect);
    void Resize(SimpleMap& mp);
    void ModifiedMap(SimpleMap& mp, vec_2i pos);
};

#endif
