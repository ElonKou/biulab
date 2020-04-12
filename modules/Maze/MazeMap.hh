#pragma once
#ifndef _MAZE_MAP_H_
#define _MAZE_MAP_H_

#include "SimpleMap.hh"

class MazeMap : public SimpleMap {
  public:
    bool    hide_others;
    vec_2i  start_pos;
    vec_2i  end_pos;
    MapType start_type;
    MapType end_type;

    MazeMap();

    ~MazeMap(void);

    /* Change the map that different from simple map. */
    void UpdateMazeMap();

    void MoveStep();

    void SetStartPos(vec_2i& pos) {
        if (!(start_pos == vec_2i(-1, -1))) {
            SetElem(start_pos, start_type);
            SetTarget(start_pos, start_type);
        }
        start_type = MapType(GetElem(pos));
        start_pos  = pos;
        SetElem(start_pos, MAP_DOOR);
        SetTarget(start_pos, MAP_DOOR);
    }

    void SetEndPos(vec_2i& pos) {
        if (!(end_pos == vec_2i(-1, -1))) {
            SetElem(end_pos, end_type);
            SetTarget(end_pos, end_type);
        }
        end_type = MapType(GetElem(pos));
        end_pos  = pos;
        SetElem(end_pos, MAP_FLAG);
        SetTarget(end_pos, MAP_FLAG);
    }

    bool CheckWallOrNot(vec_2i& pos) {
        if (pos.x >= 0 && pos.y >= 0) {
            return GetTarget(pos) == MAP_EDGE;
        } else {
            return true;
        }
    }

    bool CheckExit(vec_2i& pos) { return pos == end_pos; };
};

#endif /* __MAZE_MAP_H */