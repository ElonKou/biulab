/*================================================================
*  Copyright (C)2019 All rights reserved.
*  FileName : editor_map.cc
*  Author   : elonkou
*  Email    : elonkou@ktime.cc
*  Date     : 2019年09月24日 星期二 22时56分48秒
================================================================*/

#include "editor_map.hh"
#include "core.hh"

MapEditor::MapEditor()
    : width(16),
      height(16),
      tools(T_NONE),
      selections(S_NONE),
      selectPosCnt(0) {}

MapEditor::~MapEditor() {}

inline int MapEditor::max(int x, int y) { return x > y ? x : y; }

inline int MapEditor::min(int x, int y) { return x < y ? x : y; }

void MapEditor::checkAndSetElem(Map &mp, vec_2i pos) {
    if (tools == T_EDGE) {
        mp.setElem(pos, EDGE);
    } else if (tools == T_EMPTY) {
        mp.setElem(pos, EMPTY);
    } else if (tools == T_RUBBISH) {
        mp.setElem(pos, RUBBISH);
    } else if (tools == T_OUT) {
        mp.setElem(pos, OUT);
    }
}

void MapEditor::setTools(ToolsType tool) { tools = tool; }

void MapEditor::setSelection(SelectionsType slect) { selections = slect; }

void MapEditor::resize(Map &mp) {}

void MapEditor::modifiedMap(Map &mp, vec_2i pos) {
    if (tools != T_NONE && selections != S_NONE) {
        // Select two pos.
        if (selections == S_RECT || selections == S_LINE) {
            if (selectPosCnt == 1) {
                selectPos[1] = pos;
                selectPosCnt;
                // draw react
                int min_x = min(selectPos[0].x, selectPos[1].x);
                int max_x = max(selectPos[0].x, selectPos[1].x);
                int min_y = min(selectPos[0].y, selectPos[1].y);
                int max_y = max(selectPos[0].x, selectPos[1].y);
                if (selections == S_RECT) {
                    for (int i = min_x; i <= max_x; i++) {
                        for (int j = min_y; j <= max_y; j++) {
                            vec_2i rect_pos(i, j);
                            checkAndSetElem(mp, rect_pos);
                        }
                    }
                }
                // draw line
                if (selections == S_LINE) {
                    if (min_x == max_x) {
                        for (int i = min_y; i <= max_y - min_y; i++) {
                            vec_2i vec_pos(min_x, i);
                            checkAndSetElem(mp, vec_pos);
                        }
                    } else if (min_y == max_y) {
                        for (int i = min_x; i <= max_x - min_x; i++) {
                            vec_2i hori_pos(i, min_y);
                            checkAndSetElem(mp, hori_pos);
                        }
                    } else {
                        // build the line and  calucate all rect;
                        // float rate = (max_y - min_y) * 1.0 / (max_x - min_x);
                        // float bias = min_y + 0.5 - rate * (min_x + 0.5);
                        // for (int i = min_x; i <= max_x; i++) {
                        // }
                    }
                }
                // move forward for.
                selectPos[0] = selectPos[1];
            }
            if (selectPosCnt == 0) {
                selectPos[0] = pos;
                selectPosCnt++;
            }
        }
        // Point.
        if (selections == S_POINT) {
            // clear click history;
            selectPosCnt = 0;
            checkAndSetElem(mp, pos);
        }
        // Line.
        if (selections == S_LINE) {
        }
    }
}
