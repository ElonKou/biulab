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

using namespace std;

MapEditor::MapEditor()
    : selectPosCnt(0)
    , width(MAP_WIDTH)
    , height(MAP_HEIGHT) {
    infos.insert({int(T_NONE), {"None", map_color["None"]}});
    infos.insert({int(T_EDGE), {"Edge", map_color["Edge"]}});
    infos.insert({int(T_RUBBISH), {"Rubbish", map_color["Rubbish"]}});
    infos.insert({int(T_EMPTY), {"Empty", map_color["Empty"]}});
    infos.insert({int(T_OUT), {"Out", map_color["Out"]}});
    infos.insert({int(T_GEM), {"Gem", map_color["Gem"]}});
}

MapEditor::~MapEditor() {}

void MapEditor::CheckAndSetElem(MapBase& mp, vec_2i pos) {
    if (tools == T_EDGE) {
        mp.SetElem(pos, MAP_EDGE);
        mp.SetTarget(pos, MAP_EDGE);
    } else if (tools == T_EMPTY) {
        mp.SetElem(pos, MAP_EMPTY);
        mp.SetTarget(pos, MAP_EMPTY);
    } else if (tools == T_RUBBISH) {
        mp.SetElem(pos, MAP_RUBBISH);
        mp.SetTarget(pos, MAP_RUBBISH);
    } else if (tools == T_OUT) {
        mp.SetElem(pos, MAP_OUT);
        mp.SetTarget(pos, MAP_OUT);
    } else if (tools == T_GEM) {
        mp.SetElem(pos, MAP_GEM);
        mp.SetTarget(pos, MAP_GEM);
    }
}

void MapEditor::DrawLine(MapBase& mp, vec_2i start, vec_2i end) {
    vec_2i pos         = start;
    int    direction_x = end.x - start.x;
    int    direction_y = end.y - start.y;
    int    delta_x     = ABS(direction_x);
    int    delta_y     = ABS(direction_y);
    int    max_xy      = ((delta_x > delta_y) ? delta_x : delta_y);
    int    cnt_x       = -(max_xy / 2);
    int    cnt_y       = cnt_x;
    CheckAndSetElem(mp, start);
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
        CheckAndSetElem(mp, pos);
    }
}

void MapEditor::DrawRect(MapBase& mp, vec_2i pos_x, vec_2i pos_y) {
    int min_x = MIN(pos_x.x, pos_y.x);
    int max_x = MAX(pos_x.x, pos_y.x);
    int min_y = MIN(pos_x.y, pos_y.y);
    int max_y = MAX(pos_x.y, pos_y.y);
    for (int i = min_y; i <= max_y; i++) {
        for (int j = min_x; j <= max_x; j++) {
            vec_2i rect_pos(j, i);
            CheckAndSetElem(mp, rect_pos);
        }
    }
}

void MapEditor::DrawPoint(MapBase& mp, vec_2i pos) {
    CheckAndSetElem(mp, pos);
}

void MapEditor::DrawBlock(MapBase& mp, vec_2i pos) {
    std::vector<vec_2i> cache;
    cache.push_back(pos);
    int select_elem = mp.GetElem(pos);
    CheckAndSetElem(mp, pos);
    while (!cache.empty() && tools != select_elem) {
        vec_2i point = cache.front();
        cache.erase(cache.begin());

        vec_2i pos_left = vec_2i(-1, 0) + point;
        if (mp.InMap(pos_left) && mp.GetElem(pos_left) == select_elem) {
            cache.push_back(pos_left);
            CheckAndSetElem(mp, pos_left);
        }
        vec_2i pos_right = vec_2i(1, 0) + point;
        if (mp.InMap(pos_right) && mp.GetElem(pos_right) == select_elem) {
            cache.push_back(pos_right);
            CheckAndSetElem(mp, pos_right);
        }
        vec_2i pos_top = vec_2i(0, -1) + point;
        if (mp.InMap(pos_top) && mp.GetElem(pos_top) == select_elem) {
            cache.push_back(pos_top);
            CheckAndSetElem(mp, pos_top);
        }
        vec_2i pos_bot = vec_2i(0, 1) + point;
        if (mp.InMap(pos_bot) && mp.GetElem(pos_bot) == select_elem) {
            cache.push_back(pos_bot);
            CheckAndSetElem(mp, pos_bot);
        }
    }
}

void MapEditor::DrawAll(MapBase& mp, vec_2i pos) {
    for (int i = 0; i < mp.size.y; i++) {
        for (int j = 0; j < mp.size.x; j++) {
            CheckAndSetElem(mp, vec_2i(j, i));
        }
    }
}

void MapEditor::UpdateMap(MapBase& mp) {
    mp.UpdateSize(vec_2i(width, height));
}

void MapEditor::SetTools(ToolsType tool) { tools = tool; }

void MapEditor::SetSelection(SelectionsType slect) { selections = slect; }

void MapEditor::Resize(MapBase& mp) {}

void MapEditor::ModifiedMap(MapBase& mp, vec_2i pos) {
    if (tools != T_NONE && selections != S_NONE) {
        // Select two pos.
        if (selections == S_RECT) {
            if (selectPosCnt == 1) {
                selectPos[selectPosCnt] = pos;
                DrawRect(mp, selectPos[0], selectPos[1]);
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
                DrawLine(mp, selectPos[0], selectPos[1]);
                selectPosCnt = 0;
            } else {
                selectPos[selectPosCnt] = pos;
                selectPosCnt++;
            }
        }
        // Point.
        if (selections == S_POINT) {
            DrawPoint(mp, pos);
        }
        // Filled
        if (selections == S_BLOCK) {
            DrawBlock(mp, pos);
        }
        // All
        if (selections == S_ALL) {
            DrawAll(mp, pos);
        }
    }
}
