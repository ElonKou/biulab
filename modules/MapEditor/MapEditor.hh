#pragma once
#ifndef EDITOR_MAP_H_
#define EDITOR_MAP_H_

#include "BiuLabTypes.hh"
#include "DataBase.hh"
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

class MapEditor : public DataBase {
  private:
    int         selectPosCnt;
    vec_2i      selectPos[2];
    HistoryType histories[10];

  public:
    int width;
    int height;

    ToolsType      tools;
    SelectionsType selections;

    MapEditor();
    ~MapEditor();
    inline int abs(int x);
    inline int max(int x, int y);
    inline int min(int x, int y);
    void       checkAndSetElem(SimpleMap& mp, vec_2i pos);

    void drawLine(SimpleMap& mp, vec_2i pos_x, vec_2i pos_y);
    void drawRect(SimpleMap& mp, vec_2i pos_x, vec_2i pos_y);
    void drawPoint(SimpleMap& mp, vec_2i pos);
    void drawBlock(SimpleMap& mp, vec_2i pos);
    void drawAll(SimpleMap& mp, vec_2i pos);

    void updateMap(SimpleMap& mp);
    void setTools(ToolsType tool);
    void setSelection(SelectionsType slect);
    void resize(SimpleMap& mp);
    void modifiedMap(SimpleMap& mp, vec_2i pos);
};

#endif
