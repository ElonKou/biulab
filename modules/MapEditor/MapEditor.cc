/*================================================================
*  Copyright (C)2019 All rights reserved.
*  FileName : editor_map.cc
*  Author   : elonkou
*  Email    : elonkou@ktime.cc
*  Date     : 2019年09月24日 星期二 22时56分48秒
================================================================*/

#include "MapEditor.hh"
#include <iostream>
#include <vector>
#include "RobbieConfig.hh"
#include "cmath"

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

void MapEditor::checkAndSetElem(RobbieMap &mp, vec_2i pos) {
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

void MapEditor::drawLine(RobbieMap &mp, vec_2i start, vec_2i end) {
    vec_2i pos = start;
    int direction_x = end.x - start.x;
    int direction_y = end.y - start.y;
    int delta_x = fabs(direction_x);
    int delta_y = fabs(direction_y);
    int max_xy = ((delta_x > delta_y) ? delta_x : delta_y);
    int cnt_x = -(max_xy / 2);
    int cnt_y = cnt_x;
    checkAndSetElem(mp, start);
    for (int i = 0; i < max_xy; ++i) {
        cnt_x += delta_x;
        if (cnt_x > 0) {
            direction_x > 0 ? pos.x++ : pos.x--;
            cnt_x -= max_xy;
        }
        cnt_y += delta_y;
        if (cnt_y > 0) {
            direction_y > 0 ? pos.y++ : pos.y--;
            cnt_y -= max_xy;
        }
        checkAndSetElem(mp, pos);
    }
}

void MapEditor::drawRect(RobbieMap &mp, vec_2i pos_x, vec_2i pos_y) {
    int min_x = min(pos_x.x, pos_y.x);
    int max_x = max(pos_x.x, pos_y.x);
    int min_y = min(pos_x.y, pos_y.y);
    int max_y = max(pos_x.y, pos_y.y);
    for (int i = min_y; i <= max_y; i++) {
        for (int j = min_x; j <= max_x; j++) {
            vec_2i rect_pos(j, i);
            checkAndSetElem(mp, rect_pos);
        }
    }
}

void MapEditor::drawPoint(RobbieMap &mp, vec_2i pos) {
    checkAndSetElem(mp, pos);
}

void MapEditor::drawBlock(RobbieMap &mp, vec_2i pos) {
    std::vector<vec_2i> cache;
    cache.push_back(pos);
    int select_elem = mp.getElem(pos);
    cout << select_elem;
    checkAndSetElem(mp, pos);
    while (!cache.empty()) {
        vec_2i point = cache.front();
        cache.erase(cache.begin());

        vec_2i pos_left = vec_2i(-1, 0) + point;
        if (mp.inMap(pos_left) && mp.getElem(pos_left) == select_elem) {
            cache.push_back(pos_left);
            checkAndSetElem(mp, pos_left);
        }
        vec_2i pos_right = vec_2i(1, 0) + point;
        if (mp.inMap(pos_right) && mp.getElem(pos_right) == select_elem) {
            cache.push_back(pos_right);
            checkAndSetElem(mp, pos_right);
        }
        vec_2i pos_top = vec_2i(0, -1) + point;
        if (mp.inMap(pos_top) && mp.getElem(pos_top) == select_elem) {
            cache.push_back(pos_top);
            checkAndSetElem(mp, pos_top);
        }
        vec_2i pos_bot = vec_2i(0, 1) + point;
        if (mp.inMap(pos_bot) && mp.getElem(pos_bot) == select_elem) {
            cache.push_back(pos_bot);
            checkAndSetElem(mp, pos_bot);
        }
    }
}

void MapEditor::drawAll(RobbieMap &mp, vec_2i pos) {
    for (int i = 0; i < mp.size.y; i++) {
        for (int j = 0; j < mp.size.y; j++) {
            checkAndSetElem(mp, vec_2i(j, i));
        }
    }
}

void MapEditor::updateMap(RobbieMap &mp) {
    mp.updateSize(vec_2i(width, height));
}

void MapEditor::setTools(ToolsType tool) { tools = tool; }

void MapEditor::setSelection(SelectionsType slect) { selections = slect; }

void MapEditor::resize(RobbieMap &mp) {}

void MapEditor::modifiedMap(RobbieMap &mp, vec_2i pos) {
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
        // Filled
        if (selections == S_BLOCK) {
            drawBlock(mp, pos);
        }
        // All
        if (selections == S_ALL) {
            drawAll(mp, pos);
        }
    }
}
