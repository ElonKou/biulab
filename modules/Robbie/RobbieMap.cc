/*================================================================
*  Copyright (C)2019 All rights reserved.
*  FileName : RobbieMap.cc
*  Author   : elonkou
*  Email    : elonkou@ktime.cc
*  Date     : 2019年10月02日 星期三 11时42分59秒
================================================================*/

#include "RobbieMap.hh"
#include <fstream>
#include <iostream>
#include "Lib.hh"
#include "RobbieConfig.hh"

using namespace std;

RobbieMap::RobbieMap() {
    size = {MAP_WIDTH, MAP_HEIGHT};
    rubbish_cnt = RUBBISH_CNT;
    // Init the map
    map = nullptr;
    target = nullptr;
    path = nullptr;
    rubbish_cnt = RUBBISH_CNT;
}

RobbieMap::RobbieMap(vec_2i map_size) {
    size = map_size;
    map = new int *[size.y];
    target = new int *[size.y];
    path = new int *[size.y];
    for (int i = 0; i < size.y; i++) {
        map[i] = new int[size.x];
    }
    for (int i = 0; i < size.y; i++) {
        for (int j = 0; j < size.x; j++) {
            map[i][j] = EMPTY;
        }
    }
}

RobbieMap::~RobbieMap() {}

void RobbieMap::cleanTarget() {
    for (int i = 0; i < size.y; i++) {
        for (int j = 0; j < size.x; j++) {
            target[i][j] = map[i][j];
        }
    }
}

void RobbieMap::randomMap() {
    for (int i = 0; i < size.y; i++) {
        for (int j = 0; j < size.x; j++) {
            map[i][j] = EMPTY;
            target[i][j] = EMPTY;
            path[i][j] = PATH_EMPTY;
        }
    }
    for (int i = 0; i < size.y; i++) {
        map[i][0] = map[i][size.x - 1] = EDGE;
        target[i][0] = target[i][size.x - 1] = EDGE;
        // path[i][0] = path[i][size.x - 1] = -EDGE;
    }
    for (int i = 0; i < size.x; i++) {
        map[0][i] = map[size.y - 1][i] = EDGE;
        target[0][i] = target[size.y - 1][i] = EDGE;
        // path[0][i] = path[size.y - 1][i] = -EDGE;
    }

    // extra
    // for (int i = 0; i < 10; i++) {
    //     map[10][i] = EDGE;
    //     target[10][i] = EDGE;
    //     path[10][i] = -EDGE;
    // }
    // extra
    // for (int i = 0; i < 10; i++) {
    //     map[10-i][15] = EDGE;
    //     target[10-i][15] = EDGE;
    //     path[10-i][15] = -EDGE;
    // }
    // extra
    // for (int i = 0; i < 3; i++) {
    //     map[11+i][10] = EDGE;
    //     target[11+i][10] = EDGE;
    //     path[11+i][10] = -EDGE;
    // }

    // add random wall
    for (int i = 0; i < WALL_CNT;) {
        int temp_x = randomInt(size.x);
        int temp_y = randomInt(size.y);
        if (map[temp_y][temp_x] == 0) {
            map[temp_y][temp_x] = EDGE;
            target[temp_y][temp_x] = EDGE;
            i++;
        }
    }

    // copy into path
    for (int i = 0; i < size.y; i++) {
        for (int j = 0; j < size.x; j++) {
            if (map[i][j] == EDGE) {
                path[i][j] = -EDGE;
            }
        }
    }

    for (int i = 0; i < rubbish_cnt;) {
        int temp_x = randomInt(size.x);
        int temp_y = randomInt(size.y);
        if (map[temp_y][temp_x] == 0) {
            map[temp_y][temp_x] = RUBBISH;
            target[temp_y][temp_x] = RUBBISH;
            i++;
        }
    }
}

bool RobbieMap::inMap(vec_2i pos) {
    return (pos.x >= 0 && pos.x < size.x && pos.y >= 0 && pos.y < size.y);
}

void RobbieMap::init() {
    // cout <<size.x  << " " << size.y << endl;
    // init the std map
    map = new int *[size.y];
    target = new int *[size.y];
    for (int i = 0; i < size.y; i++) {
        map[i] = new int[size.x];
        target[i] = new int[size.x];
    }
    for (int i = 0; i < size.y; i++) {
        for (int j = 0; j < size.x; j++) {
            map[i][j] = EMPTY;
            target[i][j] = EMPTY;
        }
    }
    for (int i = 0; i < size.y; i++) {
        map[i][0] = map[i][size.x - 1] = EDGE;
        target[i][0] = target[i][size.x - 1] = EDGE;
    }
    for (int i = 0; i < size.x; i++) {
        map[0][i] = map[size.y - 1][i] = EDGE;
        target[0][i] = target[size.y - 1][i] = EDGE;
    }
    for (int i = 0; i < rubbish_cnt;) {
        int temp_x = randomInt(size.x);
        int temp_y = randomInt(size.y);
        if (map[temp_y][temp_x] == 0) {
            map[temp_y][temp_x] = RUBBISH;
            target[temp_y][temp_x] = RUBBISH;
            i++;
        }
    }
}

void RobbieMap::updateSize(vec_2i new_size) {
    int map_temp[size.y][size.x];
    for (int j = 0; j < size.y; j++) {
        for (int i = 0; i < size.x; i++) {
            map_temp[j][i] = map[j][i];
        }
    }

    map = new int *[new_size.y];
    for (int i = 0; i < new_size.y; i++) {
        map[i] = new int[new_size.x];
    }
    int min_x = size.x < new_size.x ? size.x : new_size.x;
    int min_y = size.y < new_size.y ? size.y : new_size.y;
    int max_x = size.x > new_size.x ? size.x : new_size.x;
    int max_y = size.y > new_size.y ? size.y : new_size.y;
    for (int i = 0; i < new_size.y; i++) {
        for (int j = 0; j < new_size.x; j++) {
            if (i < min_y && j < min_x) {
                map[i][j] = map_temp[i][j];
            } else {
                map[i][j] = EMPTY;
            }
        }
    }
    size = new_size;
}

void RobbieMap::loadMap(const string &load_path) {
    cout << "Loading:" << load_path << endl;
    fstream fp;
    string line;
    fp.open(load_path, ios::in);
    while (getline(fp, line)) {
        std::string str;
        size_t found = line.find("version:");
        if (found != string::npos) {
            str = line.substr(found + 8, line.size());
            float map_version = stringToNum<float>(str);
        }
        found = line.find("name:");
        if (found != string::npos) {
            str = line.substr(found + 5, line.size());
            map_name = str;
        }
        found = line.find("width:");
        if (found != string::npos) {
            str = line.substr(found + 6, line.size());
            size.x = stringToNum<int>(str);
        }
        found = line.find("height:");
        if (found != string::npos) {
            str = line.substr(found + 7, line.size());
            size.y = stringToNum<int>(str);
        }
        found = line.find("rubbish:");
        if (found != string::npos) {
            str = line.substr(found + 8, line.size());
            rubbish_cnt = stringToNum<int>(str);
        }
        found = line.find("map:");
        if (found != string::npos) {
            map = new int *[size.y];
            for (int i = 0; i < size.y; i++) {
                map[i] = new int[size.x];
                getline(fp, line);
                vector<string> vec = split(line, ",");
                for (int j = 0; j < size.x; j++) {
                    if (vec[j] == "#") {
                        map[i][j] = EDGE;
                    } else if (vec[j] == "*") {
                        map[i][j] = RUBBISH;
                    } else if (vec[j] == " ") {
                        map[i][j] = EMPTY;
                    } else if (vec[j] == ".") {
                        map[i][j] = OUT;
                    }
                }
            }
        }
    }
    fp.close();
}

void RobbieMap::saveMap(string &save_path) {
    cout << save_path << endl;
    size.print();
    fstream fp;
    fp.open(save_path, ios::out | ios::trunc);
    if (!fp) {
        cout << "Save error." << endl;
        return;
    }
    fp << "version:0.1" << endl;
    fp << "map_name:some.map" << endl;
    fp << "width:" << to_string(size.x) << endl;
    fp << "height:" << to_string(size.y) << endl;
    fp << "rubbish:" << to_string(20) << endl;
    fp << "map:" << endl;
    for (int j = 0; j < size.y; j++) {
        string x = "";
        for (int i = 0; i < size.x; i++) {
            if (map[j][i] == EDGE) {
                x = "#";
            } else if (map[j][i] == RUBBISH) {
                x = "*";
            } else if (map[j][i] == EMPTY) {
                x = " ";
            } else if (map[j][i] == OUT) {
                x = ".";
            }
            fp << x << ",";
        }
        if (j != size.y - 1) {
            fp << endl;
        }
    }
    fp.close();
}

// inline int RobbieMap::getValue(vec_2i pos) { return target[pos.y][pos.x]; }

int RobbieMap::getHash(vec_2i pos) {
    int east = getValue(vec_2i(pos.x + 1, pos.y));
    int north = getValue(vec_2i(pos.x, pos.y + 1));
    int west = getValue(vec_2i(pos.x - 1, pos.y));
    int south = getValue(vec_2i(pos.x, pos.y - 1));
    int mid = getValue(pos);
    int hash = 0;
    hash += 1 * east;
    hash += 3 * north;
    hash += 9 * west;
    hash += 27 * south;
    hash += 81 * mid;
    return hash;
}

int RobbieMap::getTarget(vec_2i pos) { return target[pos.y][pos.x]; }

void RobbieMap::setTarget(vec_2i pos, int key) { target[pos.y][pos.x] = key; }

int RobbieMap::getElem(vec_2i pos) { return map[pos.y][pos.x]; }

void RobbieMap::setElem(vec_2i pos, int key) { map[pos.y][pos.x] = key; }

int RobbieMap::doAction(vec_2i start, vec_2i offset) {
    // EDGE : -1(failed)
    // pick : 0(empty)
    // move : 1(succeed)
    vec_2i now = vec_2i(start.x + offset.x, start.y + offset.y);
    int nowVal = getValue(start);
    if (nowVal == EDGE) {
        return -1;
    } else if (nowVal == RUBBISH) {
    } else {
    }
}

inline int *RobbieMap::operator[](int row) { return map[row]; }

void RobbieMap::print(vec_2i pos) {
    printSucceed("map:\t\t\t\t\t\ttarget:\n");
    for (int i = size.y - 1; i >= 0; i--) {
        for (int j = 0; j < size.x; j++) {
            if (map[i][j] != 0) {
                if (map[i][j] == EDGE) {
                    printSucceed(map[i][j]);
                } else {
                    printOk(map[i][j]);
                }
                printSucceed(" ");
            } else {
                printf("  ");
            }
        }
        printf("  ");
        for (int j = 0; j < size.x; j++) {
            if (i == pos.y && j == pos.x) {
                printError(target[i][j]);
                printError(" ");
            } else if (target[i][j] != 0) {
                if (map[i][j] == EDGE) {
                    printSucceed(map[i][j]);
                } else {
                    printOk(map[i][j]);
                }
                printSucceed(" ");
            } else {
                printf("  ");
            }
        }
        printf("\n");
    }
}

void RobbieMap::drawFrame(PlayActions act, int *gene) {
    int len = 0;
    for (int i = 0; i < LOOP_CNT; i++) {
        int x = act.positions[i].x;
        int y = act.positions[i].y;
        if (x != 0 && y != 0) {
            path[y][x] = act.actions[i];
            len++;
        }
    }
    // for(int i =0 ;i < len - 4;i++){
    //     int x = act.positions[i].x;
    //     int y = act.positions[i].y;
    //     if (x != 0 && y != 0) {
    //         path[y][x] = 0;
    //     }
    // }
    for (int i = size.y - 1; i >= 0; i--) {
        for (int j = 0; j < size.x; j++) {
            // printf("%d ", target[i][j]);
            if (path[i][j] != PATH_EMPTY) {
                if (path[i][j] == -EDGE) {
                    printSucceed("▓▓");
                } else {
                    int act_num = path[i][j];
                    // strin xx = "";
                    switch (act_num) {
                        case UP:
                            // xx = "⇧";
                            printOk("⇧ ");
                            break;
                        case DOWN:
                            printOk("⇓ ");
                            break;
                        case LEFT:
                            printOk("⇐ ");
                            break;
                        case RIGHT:
                            printOk("⇒ ");
                            break;
                        case WAIT:
                            printOk("↻ ");
                            break;
                        case RANDOM:
                            printOk("☯ ");
                            break;
                        case PICK:
                            printOk("✾ ");
                            break;
                        default:
                            break;
                    }
                    // printOk(path[i][j]);
                }
            } else {
                // printOk("  ");
                if (target[i][j] == RUBBISH) {
                    // string xx = "✱ ";
                    printError("✱ ");
                } else {
                    printOk("  ");
                }
            }
        }
        printf("   ");
        int len = GENE_LEN / 3;
        for (int j = 0; j < len; j++) {
            int xx = (size.y - 1 - i) * len + j;
            if (xx < GENE_LEN) {
                if (xx == act.hash) {
                    printError(gene[xx]);
                } else {
                    printOk(gene[xx]);
                }
            }
        }
        if (i != 0) {
            printf("\n");
        }
    }
    cout << endl;
}