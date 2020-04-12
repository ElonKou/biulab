#include "MazeMap.hh"

using namespace std;

MazeMap::MazeMap() {
    start_pos = vec_2i(-1, -1);
    end_pos   = vec_2i(-1, -1);
}

MazeMap::~MazeMap() {}

void MazeMap::UpdateMazeMap() {
    for (int i = 0; i < size.y; i++) {
        for (int j = 0; j < size.x; j++) {
            if (map[i][j] != MAP_EDGE && map[i][j] != MAP_OUT) {
                SetElem(vec_2i(j, i), MAP_EMPTY);
                SetTarget(vec_2i(j, i), MAP_EMPTY);
            }
        }
    }
}