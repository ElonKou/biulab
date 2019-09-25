#pragma once
#ifndef EDITOR_MAP_H_
#define EDITOR_MAP_H_

#include "core.hh"

enum ToolsType { T_NONE, T_EDGE, T_OUT, T_EMPTY, T_RUBBISH };
enum SelectionsType { S_NONE, S_POINT, S_LINE, S_RECT, S_ALL };
enum ActionType { A_NONE, A_UNDO, A_REDO };

typedef struct {
    vec_2i pos[2];
    ToolsType tool;
    SelectionsType selects;
    ActionType action;
} HistoryType;

class MapEditor {
   private:
    int selectPosCnt;
    vec_2i selectPos[2];
    HistoryType histories[10];

   public:
    int width;
    int height;

    ToolsType tools;
    SelectionsType selections;

    MapEditor();
    ~MapEditor();
    inline int abs(int x);
    inline int max(int x, int y);
    inline int min(int x, int y);
    void checkAndSetElem(Map &mp, vec_2i pos);

    void drawLine(Map &mp, vec_2i pos_x, vec_2i pos_y);
    void drawRect(Map &mp, vec_2i pos_x, vec_2i pos_y);
    void drawPoint(Map &mp, vec_2i pos);

    void updateMap(Map &mp);
    void setTools(ToolsType tool);
    void setSelection(SelectionsType slect);
    void resize(Map &mp);
    void modifiedMap(Map &mp, vec_2i pos);
};

#endif
