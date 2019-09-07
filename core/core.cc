//++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// File   :xx.cpp
// Author :elonkou
// E-mail :elonkou@ktime.cc
// Date   :Sat 23 Feb 2019 02:53:10 PM CST
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#include "core.hh"
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include "lib.hh"
using namespace std;
#define random(x) (rand() % x)

// 移动规则
// 坐标从左到右x++  从上到下y++
// 0:北 4:随机移动
// 1:南 5:不动
// 2:东 6:捡东西(待增加新规则)
// 3:西
Strategy strategy[STR_CNT] = {{0, 0, 1}, {1, 0, -1}, {2, 1, 0}, {3, -1, 0},
                              {4, 0, 0}, {5, 0, 0},  {6, 0, 0}};
typedef enum action { UP, DOWN, RIGHT, LEFT, RANDOM, WAIT, PICK } ACTION;

int randomInt(int range) {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    srand(tv.tv_usec);
    return random(range);
}

float randomFloat() { return randomInt(1000000) * 1.0 / 1000000; }

vec_2i::vec_2i() {
    x = 0;
    y = 0;
}
vec_2i::vec_2i(int a, int b) : x(a), y(b) {}
vec_2i vec_2i::operator+(vec_2i other) {
    vec_2i v;
    v.x = x + other.x;
    v.y = y + other.y;
    return v;
}
void vec_2i::print() { std::cout << "(" << x << "," << y << ")"; }

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
Robbie::Robbie() {
    gene_len = GENE_LEN;
    str_len = STR_CNT;
    mutate_all = MUTATE_ALL;
    mutate_val = MUTATE_VAL;
    averScore = -1000.0;
    score = 0;
    init();
}
Robbie::~Robbie() {}
void Robbie::init() {
    for (int i = 0; i < gene_len; i++) {
        genes[i] = randomInt(str_len);
    }
    randomPos();
}
void Robbie::randomPos() {
    start.x = START_X;
    start.y = START_Y;
    pos = start;
}
Robbie Robbie::clone() {
    Robbie r = Robbie();
    for (int i = 0; i < gene_len; i++) {
        r.genes[i] = genes[i];
    }
    return r;
}
void Robbie::clear() {
    for (int i = 0; i < gene_len; i++) {
        genes[i] = GENE_CLEAR;
    }
}

void Robbie::print() {
    cout << endl;
    cout << "pos:(" << pos.x << ":" << pos.y << ")\tstart:(" << start.x << ":"
         << start.y << ")"
         << "\tscore:" << getScore() << endl;
    int next = 81;
    for (int i = 0; i < gene_len; i++) {
        if (i % next == 0 && i != 0) {
            cout << endl;
        }
        cout << genes[i];
    }
    cout << endl;
}

int Robbie::getScore() { return score; }

void Robbie::clip(Robbie &other) {
    int pos = randomInt(gene_len);
    for (int i = 0; i < pos; i++) {
        int temp = genes[i];
        genes[i] = other.genes[i];
        other.genes[i] = temp;
    }
}
Robbie Robbie::clip2(Robbie other, int pos) {
    // change the gene after pos.
    // return the new object.
    Robbie r = clone();
    for (int i = pos; i < gene_len; i++) {
        r.genes[i] = other.genes[i];
    }
    return r;
}
void Robbie::clip3(Robbie other) {}
void Robbie::mutate() {
    for (int i = 0; i < gene_len; i++) {
        int temp = randomInt(mutate_all);
        if (temp < mutate_val) {
            genes[i] = randomInt(str_len);
        }
    }
}
void Robbie::compare(Robbie other) {
    int next = 27;
    for (int i = 0; i < next; i++) {
        if (i < 10) {
            cout << " ";
        }
        printSucceed(i);
        printf(" ");
    }
    cout << endl;
    for (int i = 0; i < gene_len; i++) {
        if (i % next == 0 && i != 0) {
            cout << endl;
        }
        if (genes[i] != other.genes[i]) {
            printError(genes[i]);
            printError(other.genes[i]);
            printf(" ");
        } else {
            cout << genes[i] << other.genes[i] << " ";
        }
    }
    cout << endl;
}

void Robbie::play(Map &map) {
    // map.print(pos);
    for (int i = 0; i < LOOP_CNT; i++) {
        int result = 0;
        int hash = map.getHash(pos);
        int action = getAction(hash);
        // pos.print();
        // map.print(pos);
        while (action == RANDOM) {
            action = randomInt(STR_CNT);
        }
        switch (action) {
            case WAIT:
                break;
            case PICK:
                result = pick(action, map);
                break;
            default:
                result = move(action, map);
                break;
        }
        // std::cout << "=" << result << " ";
        // std::cout << "=" << action << " ";
    }
    // std::cout << endl << score << endl;
    // map.cleanTarget();
}

void Robbie::playOne(int cnt) {
    int res = 0;
    for (int i = 0; i < cnt; i++) {
        Map mp = Map();
        play(mp);
        res += getScore();
        score = 0;
    }
    averScore = res * 1.0 / cnt;
}

int Robbie::move(int action, Map &map) {
    vec_2i offset = vec_2i(strategy[action].wmove, strategy[action].hmove);
    vec_2i now = pos + offset;
    int val = map.getValue(now);
    if (val != EDGE) {
        pos = now;
        return action;
    } else {
        score += PUNISHMENT_EDGE;
        return -1;
    }
}

int Robbie::pick(int action, Map &map) {
    int val = map.getValue(pos);
    if (val == RUBBISH) {
        map.setTarget(pos, EMPTY);
        score += REWARD;
        return action;
    } else {
        score += PUNISHMENT_PICK;
        return -2;
    }
}

int Robbie::getAction(int hash) { return genes[hash]; }

void Robbie::save(string fileName) {}
void Robbie::load(string fileName) {}

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
Map::Map() {
    size = {MAP_WIDTH, MAP_HEIGHT};
    // Init the map
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

    for (int i = 0; i < RUBBISH_CNT;) {
        int temp_x = randomInt(size.x);
        int temp_y = randomInt(size.y);
        if (map[temp_y][temp_x] == 0) {
            map[temp_y][temp_x] = RUBBISH;
            target[temp_y][temp_x] = RUBBISH;
            i++;
        }
    }
}
Map::~Map() {}
void Map::cleanTarget() {
    for (int i = 0; i < size.y; i++) {
        for (int j = 0; j < size.x; j++) {
            target[i][j] = map[i][j];
        }
    }
}
void Map::init() {
    // init the map
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
    for (int i = 0; i < RUBBISH_CNT;) {
        int temp_x = randomInt(size.x);
        int temp_y = randomInt(size.y);
        if (map[temp_y][temp_x] == 0) {
            map[temp_y][temp_x] = RUBBISH;
            target[temp_y][temp_x] = RUBBISH;
            i++;
        }
    }
}
int inline Map::getValue(vec_2i pos) { return target[pos.y][pos.x]; }
int Map::getHash(vec_2i pos) {
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
int Map::getTarget(vec_2i pos) { return target[pos.y][pos.x]; }
void Map::setTarget(vec_2i pos, int key) { target[pos.y][pos.x] = key; }
int Map::doAction(vec_2i start, vec_2i offset) {
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

void Map::print(vec_2i pos) {
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

void Map::drawFrame(PlayActions act, int *gene) {
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

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
Controller::Controller()
    : loop_map(LOOP_MAP),
      loop_controller(LOOP_CONTROLLER),
      robbie_cnt(ROBBIE_CNT),
      max_histyory(-1000.0),
      save_path("") {
    // init controller
    float res[ROBBIE_CNT];
    float res_ori[ROBBIE_CNT];
    for (int i = 0; i < ROBBIE_CNT; i++) {
        robbies[i] = Robbie();
        scores[i] = 0.0;
        scores_tf[i] = 0.0;
    }
}
Controller::Controller(string save_path)
    : loop_map(LOOP_MAP),
      loop_controller(LOOP_CONTROLLER),
      robbie_cnt(ROBBIE_CNT),
      max_histyory(-1000.0),
      save_path(save_path) {
    // init controller
    float res[ROBBIE_CNT];
    float res_ori[ROBBIE_CNT];
    for (int i = 0; i < ROBBIE_CNT; i++) {
        robbies[i] = Robbie();
        scores[i] = 0.0;
        scores_tf[i] = 0.0;
    }
}
Controller::~Controller() {}

void Controller::train() {
    for (int k = 0; k < loop_controller; k++) {
        for (int i = 0; i < robbie_cnt; i++) {
            robbies[i].playOne(loop_map);
            scores[i] = robbies[i].averScore;
            scores_tf[i] = robbies[i].averScore;
            if (k < 1000) {
                if (scores_tf[i] < -500) {
                    scores_tf[i] = -500;
                }
                scores_tf[i] = pow(500 + scores_tf[i], 3.0) * 0.000001;
            } else {
                if (scores_tf[i] < 0) {
                    scores_tf[i] = 0;
                } else {
                    scores_tf[i] = scores_tf[i] * 50;
                    // scores_tf[i] = scores_tf[i] * 50 * 1.3;
                    // scores_tf[i] = pow(scores_tf[i], 1.3);
                }
            }
        }

        int top_id = showHisgram(k);
        if (max_histyory < scores[top_id]) {
            max_histyory = scores[top_id];
            robbies[top_id].print();
            saveRobbie(robbies[top_id], save_path);
        }
        robbies[top_id].compare(robbies[0]);

        float all = accumulate(scores_tf, scores_tf + ROBBIE_CNT, 0.0);
        for (int i = 0; i < ROBBIE_CNT; i++) {
            scores_tf[i] /= all;
            if (i != 0) {
                scores_tf[i] = scores_tf[i] + scores_tf[i - 1];
            }
        }
        cout << "========================================"
                "========================================"
             << endl;
        for (int i = 0; i < ROBBIE_CNT / 2; i++) {
            int fa = getIndex(randomFloat());
            int mo = getIndex(randomFloat());
            int pos = randomInt(GENE_LEN);
            robbies_temp[i * 2] = robbies[fa].clip2(robbies[mo], pos);
            robbies_temp[i * 2 + 1] = robbies[mo].clip2(robbies[fa], pos);
        }
        for (int i = 0; i < ROBBIE_CNT; i++) {
            robbies[i] = robbies_temp[i];
            robbies[i].mutate();
        }
    }
}

void Controller::print_str() {
    std::cout << "   0  " << endl;
    std::cout << " 3 4 2" << endl;
    std::cout << "   1  " << endl;
}

void Controller::playScreen(Robbie &rob, Map &map) {
    PlayActions act;
    for (int i = 0; i < LOOP_CNT; i++) {
        print_str();
        int result = 0;
        int hash = map.getHash(rob.pos);
        int action = rob.getAction(hash);
        usleep(100000);
        act.hash = hash;
        act.actions[i] = action;
        act.positions[i] = rob.pos;
        map.drawFrame(act, rob.genes);
        cout << i << " : " << rob.score << "hash:" << hash << endl;
        while (action == RANDOM) {
            action = randomInt(STR_CNT);
        }
        switch (action) {
            case WAIT:
                break;
            case PICK:
                result = rob.pick(action, map);
                break;
            default:
                result = rob.move(action, map);
                break;
        }
        // std::cout << "=" << result << " ";
        // std::cout << "=" << action << " ";
    }
    // std::cout << endl << score << endl;
    // map.cleanTarget();
}

Robbie Controller::loadRobbie(string robbie_path) {
    Robbie rob;
    ifstream fp;
    fp.open(robbie_path);
    string data;
    string ss;
    while (getline(fp, ss)) {
        data += ss;
    }
    for (int i = 0; i < data.size(); i++) {
        rob.genes[i] = int(data[i] - '0');
    }
    fp.close();
    return rob;
}
void Controller::saveRobbie(Robbie &rob, string robbie_path) {
    int score = int(rob.averScore);
    if(save_path != ""){
        robbie_path += to_string(score) + ".txt";
        ofstream fp;
        fp.open(robbie_path);
        for (int i = 0; i < rob.gene_len; i++) {
            if (i % 81 == 0 && i != 0) {
                fp << "\n";
            }
            fp << rob.genes[i];
        }
        fp.close();
        cout << robbie_path << " saved." << endl;
    }
}

int Controller::getIndex(float random_index) {
    int i = 0;
    while (scores_tf[i] < random_index) {
        i++;
    }
    return i;
}

int Controller::showHisgram(int num) {
    int minIndex = 0;
    int maxIndex = 0;
    float minData = 1000;
    float maxData = -1000;
    float sum = 0.0;
    int nevCnt = 0;
    for (int i = 0; i < ROBBIE_CNT; i++) {
        sum += scores[i];
        if (scores[i] > 0) {
            nevCnt++;
        }
        if (scores[i] > maxData) {
            maxIndex = i;
            maxData = scores[i];
        }
        if (scores[i] < minData) {
            minIndex = i;
            minData = scores[i];
        }
    }
    int clipCnt = 20;
    float res = (maxData - minData) * 1.0;
    float step = res / clipCnt;
    int shows[clipCnt] = {0};
    for (int i = 0; i < ROBBIE_CNT; i++) {
        int index = int((scores[i] - minData) / step);
        shows[index]++;
    }
    cout << num << "\tID:" << maxIndex << "\tCLIP_CNT:" << clipCnt
         << "\tSTEP:" << step << "\tAVER:" << setw(5) << setprecision(5)
         << sum / ROBBIE_CNT << "\t>=0:" << nevCnt << "\tMIN:" << minData
         << "\tMAX:" << maxData << "\tHIS_MAX:" << max_histyory << endl;
    for (int i = 0; i < clipCnt; i++) {
        cout << std::left << setw(9) << minData + i * step << std::right
             << setw(9) << minData + (i + 1) * step << ":";
        for (int j = 0; j < shows[i]; j++) {
            cout << "*";
        }
        cout << endl;
    }
    return maxIndex;
}