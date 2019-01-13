//++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// File   :core.cpp
// Author :elonkou
// E-mail :elonkou@ktime.cc
// Date   :Mon 07 Jan 2019 05:33:16 PM CST
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#include "core_genetic.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <algorithm>
#include <iostream>
#include "lib.h"
using namespace std;
#define random(x) (rand() % x)

// 移动规则
// 坐标从左到右x++  从上到下y++
// 0:北 4:不动
// 1:南 5:随机移动
// 2:东 6:捡东西(待增加新规则)
// 3:西 7:捡东西
Strategy strategy[STR_CNT] = {{0, 0, -1}, {1, 0, 1}, {2, 1, 0}, {3, -1, 0},
                              {4, 0, 0},  {5, 0, 0}, {6, 0, 0}, {7, 0, 0}};
long robbieID = 0;

void printAction(int action) {
    // cout << action;
    switch (action) {
        case -2:
            printSome("&");
            break;
        case -1:
            printSome("#");
            break;
        case 0:
            printSucceed("↑");
            break;
        case 1:
            printSucceed("↓");
            break;
        case 2:
            printSucceed("→");
            break;
        case 3:
            printSucceed("←");
            break;
        case 4:
            printSucceed("+");
            break;
        case 5:
            printSome("*");
            break;
        case 6:
            printError("@");
            break;
        case 7:
            printError("@");
            break;
        default:
            break;
    }
}
void print_strategy() {
    for (int i = 0; i < STR_CNT; i++) {
        printAction(i);
        cout << ":" << strategy[i].wmove << "" << strategy[i].hmove << ", ";
    }
    cout << endl;
}
bool cmpCell(Cell a, Cell b) {
    return a.score > b.score;
}
int randomInt(int range) {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    srand(tv.tv_usec);
    return random(range);
}
// +++++++++++++++++++++++++++++++++++++++++++++++++++++
vec_2i::vec_2i() {}
vec_2i::vec_2i(int a, int b) : x(a), y(b) {}
Cell ::Cell() : index(0), score(0.0) {}
// +++++++++++++++++++++++++++++++++++++++++++++++++++++
Map::Map() {
    Map::size = {MAP_WIDTH, MAP_HEIGHT};
    // Init the map
    for (int i = 0; i < Map::size.y; i++) {
        for (int j = 0; j < Map::size.x; j++) {
            Map::map[i][j] = EMPTY;
            Map::target[i][j] = EMPTY;
        }
    }
    for (int i = 0; i < Map::size.y; i++) {
        Map::map[i][0] = Map::map[i][Map::size.x - 1] = EDGE;
        Map::target[i][0] = Map::target[i][Map::size.x - 1] = EDGE;
    }
    for (int i = 0; i < Map::size.x; i++) {
        Map::map[0][i] = Map::map[Map::size.y - 1][i] = EDGE;
        Map::target[0][i] = Map::target[Map::size.y - 1][i] = EDGE;
    }
    for (int i = 0; i < RUBBISH_CNT;) {
        int temp_x = randomInt(Map::size.x);
        int temp_y = randomInt(Map::size.y);
        if (Map::map[temp_y][temp_x] == 0) {
            Map::map[temp_y][temp_x] = RUBBISH;
            Map::target[temp_y][temp_x] = RUBBISH;
            i++;
        }
    }
}

Map::~Map() {}
vec_2i Map::getSize() {
    return vec_2i(Map::size.x, Map::size.y);
}
void Map::print(vec_2i pos) {
    printSucceed("map:\t\t\t\t\t\ttarget:\n");
    for (int i = 0; i < Map::size.y; i++) {
        // for (int i = 0; i < 5; i++) {
        for (int j = 0; j < Map::size.x; j++) {
            if (Map::map[i][j] != 0) {
                cout << Map::map[i][j] << " ";
            } else {
                cout << "  ";
            }
            // cout << Map::map[i][j] << " ";
        }
        cout << "  ";
        for (int j = 0; j < Map::size.x; j++) {
            if (i == pos.y && j == pos.x) {
                printError(Map::target[i][j]);
                printError(" ");
            } else if (Map::target[i][j] != 0) {
                cout << Map::target[i][j] << " ";
            } else {
                cout << "  ";
            }
            // cout << Map::target[i][j] << " ";
            // printf("%d ", Map::target[i][j]);
        }
        cout << endl;
    }
}
void Map::cleanTarget() {
    for (int i = 0; i < Map::size.y; i++) {
        for (int j = 0; j < Map::size.x; j++) {
            Map::target[i][j] = Map::map[i][j];
        }
    }
}
void Map::init() {
    // 初始化地图
    for (int i = 0; i < Map::size.y; i++) {
        for (int j = 0; j < Map::size.x; j++) {
            Map::map[i][j] = EMPTY;
            Map::target[i][j] = EMPTY;
        }
    }
    for (int i = 0; i < Map::size.y; i++) {
        Map::map[i][0] = Map::map[i][Map::size.x - 1] = EDGE;
        Map::target[i][0] = Map::target[i][Map::size.x - 1] = EDGE;
    }
    for (int i = 0; i < Map::size.x; i++) {
        Map::map[0][i] = Map::map[Map::size.y - 1][i] = EDGE;
        Map::target[0][i] = Map::target[Map::size.y - 1][i] = EDGE;
    }
    for (int i = 0; i < RUBBISH_CNT;) {
        int temp_x = randomInt(Map::size.x);
        int temp_y = randomInt(Map::size.y);
        if (Map::map[temp_y][temp_x] == 0) {
            Map::map[temp_y][temp_x] = RUBBISH;
            Map::target[temp_y][temp_x] = RUBBISH;
            i++;
        }
    }
}
int inline Map::getValue(vec_2i pos) {
    // return Map::map[pos.y][pos.x];
    return Map::target[pos.y][pos.x];
}
int Map::getHash(vec_2i pos) {
    int east = Map::getValue(vec_2i(pos.x + 1, pos.y));
    int north = Map::getValue(vec_2i(pos.x, pos.y - 1));
    int west = Map::getValue(vec_2i(pos.x - 1, pos.y));
    int south = Map::getValue(vec_2i(pos.x, pos.y + 1));
    int mid = Map::getValue(pos);
    int hash = 0;
    hash *= 3;
    hash += east;
    hash *= 3;
    hash += north;
    hash *= 3;
    hash += west;
    hash *= 3;
    hash += south;
    hash *= 3;
    hash += mid;
    // Map::target[pos.y][pos.x] = hash;
    // cout << "(" << pos.x << pos.y << ")=" << east << north << west << south
    //      << mid << " ";
    return hash;
}
int Map::getTarget(vec_2i pos) {
    return Map::target[pos.y][pos.x];
}
void Map::setTarget(vec_2i pos, int key) {
    Map::target[pos.y][pos.x] = key;
}
int Map::doAction(vec_2i start, vec_2i offset) {
    // EDGE : -1(failed)
    // pick : 0(empty)
    // move : 1(succeed)
    vec_2i now = vec_2i(start.x + offset.x, start.y + offset.y);
    int nowVal = Map::getValue(start);
    if (nowVal == EDGE) {
        return -1;
    } else if (nowVal == RUBBISH) {
    } else {
    }
}
// +++++++++++++++++++++++++++++++++++++++++++++++++++++

Gene::Gene() : len(GENE_LEN) {
    Gene::clear();
    Gene::init();
}

Gene::~Gene() {}
Gene Gene::clone() {
    Gene temp;
    for (int i = 0; i < temp.len; i++) {
        temp.genes[i] = Gene::genes[i];
    }
    return temp;
}
Gene Gene::create() {
    Gene temp = Gene::clone();
    temp.mutate();
    return temp;
}
Gene Gene::create(Gene other) {
    Gene temp = Gene::clone();
    Gene temp2 = other.clone();
    temp.clip(temp2);
    temp.mutate();
    return temp;
}
void Gene::clear() {
    for (int i = 0; i < GENE_LEN; i++) {
        Gene::genes[i] = GENE_CLEAR;
    }
}
void Gene::init() {
    for (int i = 0; i < GENE_LEN; i++) {
        Gene::genes[i] = randomInt(STR_CNT);
    }
}
void Gene::clip(Gene other) {
    // Gene temp = Gene::clone();
    for (int i = 0; i < CLIP_CNT; i++) {
        int posA = randomInt(Gene::len);
        int posB = randomInt(Gene::len);
        int start = min(posA, posB);
        int end = max(posA, posB);
        int data = 0;
        for (int j = start; j < end; j++) {
            // data = temp.genes[j];
            // temp.genes[j] = other.genes[j];
            // other.genes[j] = data;
            data = Gene::genes[j];
            Gene::genes[j] = other.genes[j];
            other.genes[j] = data;
        }
    }
}
void Gene::clip2(Gene other) {
    // Gene temp = Gene::clone();
    for (int i = 0; i < CLIP_CNT; i++) {
        int posA = randomInt(Gene::len);
        int posB = randomInt(Gene::len);
        int start = min(posA, posB);
        int end = max(posA, posB);
        int data = 0;
        for (int j = start; j < end; j++) {
            // data = temp.genes[j];
            // temp.genes[j] = other.genes[j];
            // other.genes[j] = data;
            data = Gene::genes[j];
            Gene::genes[j] = other.genes[j];
            other.genes[j] = data;
        }
    }
}
void Gene::mutate() {
    for (int i = 0; i < Gene::len; i++) {
        int temp = randomInt(MUTATE_ALL);
        if (temp < MUTATE_VAL) {
            Gene::genes[i] = randomInt(STR_CNT);
        }
    }
}
void Gene::print() {
    int next = 81;
    int temp[8] = {0};
    for (int i = 0; i < Gene::len; i++) {
        temp[Gene::genes[i]]++;
        if (i % next == 0 && i != 0) {
            cout << endl;
        }
        cout << Gene::genes[i];
    }
    cout << endl;

    // for (int i = 0; i < 8; i++) {
    //     cout << i << ":" << temp[i] << " ";
    // }
    // cout << endl;
}
void Gene::compare(Gene other) {
    int next = 27;
    for (int i = 0; i < next; i++) {
        if (i < 10) {
            cout << " ";
        }
        printSucceed(i);
        printf(" ");
    }
    cout << endl;
    for (int i = 0; i < Gene::len; i++) {
        if (i % next == 0 && i != 0) {
            cout << endl;
        }
        if (Gene::genes[i] != other.genes[i]) {
            printError(Gene::genes[i]);
            printError(other.genes[i]);
            printf(" ");
        } else {
            cout << Gene::genes[i] << other.genes[i] << " ";
        }
    }
    cout << endl;
}
int Gene::getAction(int hash) {
    return Gene::genes[hash];
}

// +++++++++++++++++++++++++++++++++++++++++++++++++++++
Robbie::Robbie() {
    // Init the genes
    for (int i = 0; i < PARENT_CNT; i++) {
        Robbie::parentId[i] = -1;
    }
    Robbie::genes = Gene();
    Robbie::id = robbieID++;
    Robbie::score = 0.0;
    for (int i = 0; i < LOOP_CNT; i++) {
        Robbie::state[i] = 0;
    }
    Robbie::randomPos();
}
Robbie::~Robbie() {}
void Robbie::randomPos() {
    Robbie::start = vec_2i(1, 1);
    // Robbie::start =
    //     vec_2i(randomInt(MAP_WIDTH - 2) + 1, randomInt(MAP_HEIGHT - 2) + 1);
    Robbie::pos = Robbie::start;
}
void Robbie::cleanState() {
    for (int i = 0; i < LOOP_CNT; i++) {
        Robbie::state[i] = -3;
    }
}
Robbie Robbie::marray() {
    Robbie temp;
    temp.parentId[0] = Robbie::id;
    temp.genes = Robbie::genes.create();
    return temp;
}
Robbie Robbie::marray(Robbie spouse) {
    Robbie temp;
    temp.parentId[0] = Robbie::id;
    temp.parentId[1] = spouse.id;
    temp.genes = Robbie::genes.create(spouse.genes);
    return temp;
}
vec_2i Robbie::getPos() {
    return Robbie::pos;
}
void Robbie::print() {
    printSucceed("robbieId:");
    printSucceed(Robbie::id);
    printSucceed("  parentId:");
    printSucceed(Robbie::parentId[0]);
    printSucceed("|");
    printSucceed(Robbie::parentId[1]);
    // printSucceed("  pos:");
    // printSucceed(Robbie::pos.x);
    // printSucceed(",");
    // printSucceed(Robbie::pos.y);
    printSucceed("  score:");
    // printSucceed(Robbie::score);
    cout << Robbie::score;
    printSucceed("  start:");
    printSucceed(Robbie::start.x);
    printSucceed(",");
    printSucceed(Robbie::start.y);
    printSucceed("  genes:\n");
    // for (int i = 0; i < LOOP_CNT; i++) {
    //     printAction(Robbie::state[i]);
    // }
    // cout << endl;
    Robbie::genes.print();
}
void Robbie::compare(Robbie spouse) {
    Robbie::genes.compare(spouse.genes);
}
int Robbie::move(int action, vec_2i pos, Map map) {
    if (action == 5) {
        action = randomInt(5);
    }
    if (action <= 4) {
        int xOffset = strategy[action].wmove;
        int yOffset = strategy[action].hmove;
        vec_2i now = vec_2i(pos.x + xOffset, pos.y + yOffset);
        int val = map.getValue(now);
        if (val != EDGE) {
            Robbie::pos = now;
            return action;
        } else {
            Robbie::score += PUNISHMENT_EDGE;
            return -1;
        }
    }
}
int Robbie::pick(int action, vec_2i pos, Map& map) {
    if (action == 7 || action == 6) {
        int val = map.getValue(pos);
        if (val == RUBBISH) {
            map.setTarget(pos, EMPTY);
            Robbie::score += REWARD;
            return action;
        } else {
            Robbie::score += PUNISHMENT_PICK;
            return -2;
        }
    }
}
float Robbie::getScore() {
    return Robbie::score;
}
void Robbie::play(Map& map) {
    for (int i = 0; i < LOOP_ONE; i++) {
        Robbie::randomPos();
        for (int i = 0; i < LOOP_CNT; i++) {
            // map.print(Robbie::getPos());
            int hash = map.getHash(Robbie::getPos());
            int action = Robbie::genes.getAction(hash);
            int result = 0;
            // cout << hash << " ";
            // cout << hash << "=" << action << " ";
            // cout << "hash:" << hash << " action:" << action << endl;
            // cout << "(" << pos.x << "," << pos.y << ")"
            //      << "=" << hash << ":";
            switch (action) {
                case 0:
                case 1:
                case 2:
                case 3:
                case 4:
                case 5:
                    result = Robbie::move(action, pos, (Map&)map);
                    break;
                case 6:
                case 7:
                    result = Robbie::pick(action, pos, map);
                    break;
                default:
                    break;
            }
            Robbie::state[i] = result;
        }
        map.cleanTarget();
    }
    Robbie::score /= LOOP_ONE;
    Robbie::score /= LOOP_CNT;
}

// +++++++++++++++++++++++++++++++++++++++++++++++++++++
Controller::Controller()
    : loopCnt(LOOP_CONTROLLER), robbieCnt(ROBBIE_CNT), generation(0) {
    for (int i = 0; i < Controller::robbieCnt; i++) {
        Controller::robbies[i] = Robbie();
        Controller::scores[i] = Cell();
    }
    Controller::map = Map();
}

Controller::~Controller() {}
void Controller::init() {}
void Controller::loop() {
    for (int i = 0; i < Controller::loopCnt; i++) {
        // cout << "generation:" << Controller::generation << endl;
        Controller::run();
        Controller::select();
        Controller::generate();
    }
}

void Controller::run() {
    for (int i = 0; i < Controller::robbieCnt; i++) {
        Controller::robbies[i].play(Controller::map);
        Controller::map.init();
        Controller::scores[i].score = Controller::robbies[i].getScore();
        Controller::scores[i].index = i;
    }
}
void Controller::select() {
    sort(Controller::scores, Controller::scores + Controller::robbieCnt,
         cmpCell);
    Controller::robbies[Controller::scores[0].index].print();
}

void Controller::generate() {
    for (int i = 0; i < Controller::robbieCnt; i++) {
        Controller::temps[i] = Controller::robbies[i];
    }
    for (int i = 0; i < Controller::robbieCnt;) {
        int indexA = randomInt(robbieCnt / 2);
        int indexB = randomInt(robbieCnt / 2);
        indexA = Controller::scores[indexA].index;
        indexB = Controller::scores[indexB].index;
        // for (int j = 0; j < 10; j++) {
        //     Controller::robbies[i++] =
        //         Controller::temps[indexA].marray(Controller::temps[indexB]);
        // }
        Controller::robbies[i++] =
            Controller::temps[indexA].marray(Controller::temps[indexB]);
        Controller::robbies[i++] =
            Controller::temps[indexB].marray(Controller::temps[indexA]);
    }
    Controller::generation++;
}
void Controller::print() {
    Controller::map.print(Controller::robbies[0].getPos());
    cout << "loopCnt:" << Controller::loopCnt
         << " robbieCnt:" << Controller::robbieCnt << endl;
    // for (int i = 0; i < Controller::robbieCnt; i++) {
    // Controller::robbies[i].print();
    // Controller::robbies[Controller::scores[i].index].print();
    // << Controller::scores[i].index << ":" << Controller::scores[i].score
    // << " ";
    // }
    Controller::robbies[Controller::scores[0].index].print();
    // Controller::robbies[Controller::scores[0].index + 20].print();
}