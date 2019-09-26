/*================================================================
*  Copyright (C)2019 All rights reserved.
*  FileName : editor_map.cc
*  Author   : elonkou
*  Email    : elonkou@ktime.cc
*  Date     : 2019年09月24日 星期二 22时56分48秒
================================================================*/

#include "editor_map.hh"
#include <iostream>
#include "cmath"
#include "core.hh"

using namespace std;

MapEditor::MapEditor()
    : width(MAP_WIDTH),
      height(MAP_HEIGHT),
      tools(T_NONE),
      selections(S_NONE),
      selectPosCnt(0) {}

MapEditor::~MapEditor() {}

inline int MapEditor::abs(int x) { return x > 0 ? x : -x; }

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

void MapEditor::drawLine(Map &mp, vec_2i pos_x, vec_2i pos_y) {
    int min_y = min(pos_x.y, pos_y.y);
    int max_y = max(pos_x.y, pos_y.y);
    int min_x = min(pos_x.x, pos_y.x);
    int max_x = max(pos_x.x, pos_y.x);
    if (pos_x.x == pos_y.x) {
        for (int i = min_y; i <= max_y; i++) {
            checkAndSetElem(mp, vec_2i(pos_x.x, i));
        }
    } else if (pos_x.y == pos_y.y) {
        for (int i = min_x; i <= max_x; i++) {
            checkAndSetElem(mp, vec_2i(i, pos_x.y));
        }
    } else {
        float rate = (pos_y.y - pos_x.y) * 1.0 / (pos_y.x - pos_x.x);
        cout << "rate:" << rate << endl;
        if (fabs(rate + 1) < 1.0e-6) {
            for (int i = 0; i <= max_x - min_x; i++) {
                checkAndSetElem(mp, vec_2i(min_x + i, max_y - i));
                // cout << "VEC" << min_x + i << "," << min_y + i << endl;
            }
        } else if (fabs(rate - 1) < 1.0e-6) {
            for (int i = 0; i <= max_x - min_x; i++) {
                checkAndSetElem(mp, vec_2i(min_x + i, min_y + i));
                // cout << "HORI" << min_x + i << "," << min_y + i << endl;
            }
        } else 
        // if (rate > 1 || rate < -1) {
        //     int temp = pos_x.x;
        //     pos_x.x = pos_x.y;
        //     pos_x.y = temp;
        //     temp = pos_y.x;
        //     pos_y.x = pos_y.y;
        //     pos_y.y = temp;
        // }
        // swap the pos and do check.
        if (rate > -1 && rate < 1) {
            cout << "+++" << endl;
            int dx = abs(pos_y.x - pos_x.x);
            int dy = abs(pos_y.y - pos_x.y);
            int p = 2 * dy - dx;
            int twoDy = 2 * dy;
            int twoDyMinusDx = 2 * (dy - dx);
            if(rate < 0){
                twoDy *= -1;
                // twoDyMinusDx *= -1;
            }
            int x, y;
            if (pos_x.x > pos_y.x) {
                x = pos_y.x;
                y = pos_y.y;
                pos_y.x = pos_x.x;
            } else {
                x = pos_x.x;
                y = pos_x.y;
            }
            checkAndSetElem(mp, vec_2i(x, y));
            while (x < pos_y.x) {
                x++;
                if (p < 0) {
                    p += twoDy;
                } else {
                    y++;
                    p += twoDyMinusDx;
                }
                checkAndSetElem(mp, vec_2i(x, y));
            }
        }
        //
    }
}

void MapEditor::drawRect(Map &mp, vec_2i pos_x, vec_2i pos_y) {
    int min_x = min(pos_x.x, pos_y.x);
    int max_x = max(pos_x.x, pos_y.x);
    int min_y = min(pos_x.y, pos_y.y);
    int max_y = max(pos_x.y, pos_y.y);
    cout << min_x << " " << min_y << " " << max_x << " " << max_y << endl;
    for (int i = min_y; i <= max_y; i++) {
        for (int j = min_x; j <= max_x; j++) {
            vec_2i rect_pos(j, i);
            checkAndSetElem(mp, rect_pos);
        }
    }
}

void MapEditor::drawPoint(Map &mp, vec_2i pos) { checkAndSetElem(mp, pos); }

void MapEditor::updateMap(Map &mp) { mp.updateSize(vec_2i(width, height)); }

void MapEditor::setTools(ToolsType tool) { tools = tool; }

void MapEditor::setSelection(SelectionsType slect) { selections = slect; }

void MapEditor::resize(Map &mp) {}

void MapEditor::modifiedMap(Map &mp, vec_2i pos) {
    if (tools != T_NONE && selections != S_NONE) {
        // Select two pos.
        if (selections == S_RECT) {
            if (selectPosCnt == 1) {
                selectPos[selectPosCnt] = pos;
                drawRect(mp, selectPos[0], selectPos[1]);
                selectPosCnt = 0;
            } else {
                selectPos[selectPosCnt] = pos;
                selectPosCnt++;
            }
        }
        // Line.
        if (selections == S_LINE) {
            if (selectPosCnt == 1) {
                selectPos[selectPosCnt] = pos;
                drawLine(mp, selectPos[0], selectPos[1]);
                selectPosCnt = 0;
            } else {
                selectPos[selectPosCnt] = pos;
                selectPosCnt++;
            }
        }
        // Point.
        if (selections == S_POINT) {
            drawPoint(mp, pos);
        }
    }
}
