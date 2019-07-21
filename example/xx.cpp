//++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// File   :xx.cpp
// Author :elonkou
// E-mail :elonkou@ktime.cc
// Date   :Sat 23 Feb 2019 02:53:10 PM CST
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#include "xx.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <algorithm>
#include <iostream>
#include "lib.hpp"
using namespace std;
#define random(x) (rand() % x)

// 移动规则
// 坐标从左到右x++  从上到下y++
// 0:北 4:不动
// 1:南 5:随机移动
// 2:东 6:捡东西(待增加新规则)
// 3:西
Strategy strategy[STR_CNT] = {{0, 0, 1}, {1, 0, -1}, {2, 1, 0}, {3, -1, 0}, {4, 0, 0}, {5, 0, 0}, {6, 0, 0}};


int randomInt(int range)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    srand(tv.tv_usec);
    return random(range);
}

float randomFloat()
{
    return randomInt(1000000) * 1.0 / 1000000;
}

vec_2i::vec_2i()
{
    x = 0;
    y = 0;
}
vec_2i::vec_2i(int a, int b) : x(a), y(b) {}
vec_2i vec_2i::operator+(vec_2i other)
{
    vec_2i v;
    v.x = x + other.x;
    v.y = y + other.y;
    return v;
}
void vec_2i::print()
{
    std::cout << "(" << x << "," << y << ")";
}

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
Robbie::Robbie()
{
    gene_len = GENE_LEN;
    str_len = STR_CNT;
    mutate_all = MUTATE_ALL;
    mutate_val = MUTATE_VAL;
    init();
}
Robbie::~Robbie() {}
void Robbie::init()
{
    for (int i = 0; i < gene_len; i++)
    {
        genes[i] = randomInt(str_len);
    }
    randomPos();
}
void Robbie::randomPos()
{
    start.x = 1;
    start.y = 1;
    pos = start;
}
Robbie Robbie::clone()
{
    Robbie r = Robbie();
    for (int i = 0; i < gene_len; i++)
    {
        r.genes[i] = genes[i];
    }
    return r;
}
void Robbie::clear()
{
    for (int i = 0; i < gene_len; i++)
    {
        genes[i] = GENE_CLEAR;
    }
}

void Robbie::print()
{
    cout << endl;
    cout << "pos:(" << pos.x << ":" << pos.y << ")\tstart:(" << start.x << ":"
         << start.y << ")" << endl;
    int next = 81;
    for (int i = 0; i < gene_len; i++)
    {
        if (i % next == 0 && i != 0)
        {
            cout << endl;
        }
        cout << genes[i];
    }
    cout << endl;
}

int Robbie::getScore()
{
    return score;
}

void Robbie::clip(Robbie &other)
{
    int pos = randomInt(gene_len);
    for (int i = 0; i < pos; i++)
    {
        int temp = genes[i];
        genes[i] = other.genes[i];
        other.genes[i] = temp;
    }
}
Robbie Robbie::clip2(Robbie other, int pos)
{
    // change the gene after pos.
    // return the new object.
    Robbie r = clone();
    for (int i = pos; i < gene_len; i++)
    {
        r.genes[i] = other.genes[i];
    }
    return r;
}
void Robbie::clip3(Robbie other) {}
void Robbie::mutate()
{
    for (int i = 0; i < gene_len; i++)
    {
        int temp = randomInt(mutate_all);
        if (temp < mutate_val)
        {
            genes[i] = randomInt(str_len);
        }
    }
}
void Robbie::compare(Robbie other)
{
    int next = 27;
    for (int i = 0; i < next; i++)
    {
        if (i < 10)
        {
            cout << " ";
        }
        printSucceed(i);
        printf(" ");
    }
    cout << endl;
    for (int i = 0; i < gene_len; i++)
    {
        if (i % next == 0 && i != 0)
        {
            cout << endl;
        }
        if (genes[i] != other.genes[i])
        {
            printError(genes[i]);
            printError(other.genes[i]);
            printf(" ");
        }
        else
        {
            cout << genes[i] << other.genes[i] << " ";
        }
    }
    cout << endl;
}

void Robbie::play(Map &map)
{
    // map.print(pos);
    for (int i = 0; i < LOOP_CNT; i++)
    {
        int result = 0;
        int hash = map.getHash(pos);
        int action = getAction(hash);
        // pos.print();
        // map.print(pos);
        while (action == 5)
        {
            action = randomInt(7);
        }
        switch (action)
        {
        case 0:
            result = Robbie::move(action, map);
            break;
        case 1:
            result = Robbie::move(action, map);
            break;
        case 2:
            result = Robbie::move(action, map);
            break;
        case 3:
            result = Robbie::move(action, map);
            break;
        case 4:
            break;
        case 5:
            result = Robbie::move(action, map);
            break;
        case 6:
            result = Robbie::pick(action, map);
            break;
        }
        // std::cout << "=" << result << " ";
        // std::cout << "=" << action << " ";
    }
    // std::cout << endl << score << endl;
    // map.cleanTarget();
}

void Robbie::playScreen(Map &map)
{
    // map.print(pos);
    for (int i = 0; i < LOOP_CNT; i++)
    {
        int result = 0;
        int hash = map.getHash(pos);
        int action = getAction(hash);
        // pos.print();
        // map.print(pos);
        while (action == 5)
        {
            action = randomInt(7);
        }
        switch (action)
        {
        case 0:
            result = Robbie::move(action, map);
            break;
        case 1:
            result = Robbie::move(action, map);
            break;
        case 2:
            result = Robbie::move(action, map);
            break;
        case 3:
            result = Robbie::move(action, map);
            break;
        case 4:
            break;
        case 5:
            result = Robbie::move(action, map);
            break;
        case 6:
            result = Robbie::pick(action, map);
            break;
        }
        // std::cout << "=" << result << " ";
        // std::cout << "=" << action << " ";
    }
    // std::cout << endl << score << endl;
    // map.cleanTarget();
}

float Robbie::playOne()
{
    int res = 0;
    for (int i = 0; i < LOOP_MAP; i++)
    {
        Map mp = Map();
        play(mp);
        res += getScore();
        score = 0;
    }
    return res * 1.0 / LOOP_MAP;
}

int Robbie::move(int action, Map &map)
{
    vec_2i offset = vec_2i(strategy[action].wmove, strategy[action].hmove);
    vec_2i now = pos + offset;
    int val = map.getValue(now);
    if (val != EDGE)
    {
        pos = now;
        return action;
    }
    else
    {
        score += PUNISHMENT_EDGE;
        return -1;
    }
}

int Robbie::pick(int action, Map &map)
{
    int val = map.getValue(pos);
    if (val == RUBBISH)
    {
        map.setTarget(pos, EMPTY);
        score += REWARD;
        return action;
    }
    else
    {
        score += PUNISHMENT_PICK;
        return -2;
    }
}

int Robbie::getAction(int hash)
{
    return genes[hash];
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
Map::Map()
{
    size = {MAP_WIDTH, MAP_HEIGHT};
    // Init the map
    for (int i = 0; i < size.y; i++)
    {
        for (int j = 0; j < size.x; j++)
        {
            map[i][j] = EMPTY;
            target[i][j] = EMPTY;
        }
    }
    for (int i = 0; i < size.y; i++)
    {
        map[i][0] = map[i][size.x - 1] = EDGE;
        target[i][0] = target[i][size.x - 1] = EDGE;
    }
    for (int i = 0; i < size.x; i++)
    {
        map[0][i] = map[size.y - 1][i] = EDGE;
        target[0][i] = target[size.y - 1][i] = EDGE;
    }
    for (int i = 0; i < RUBBISH_CNT;)
    {
        int temp_x = randomInt(size.x);
        int temp_y = randomInt(size.y);
        if (map[temp_y][temp_x] == 0)
        {
            map[temp_y][temp_x] = RUBBISH;
            target[temp_y][temp_x] = RUBBISH;
            i++;
        }
    }
}
Map::~Map() {}
void Map::cleanTarget()
{
    for (int i = 0; i < size.y; i++)
    {
        for (int j = 0; j < size.x; j++)
        {
            target[i][j] = map[i][j];
        }
    }
}
void Map::init()
{
    // init the map
    for (int i = 0; i < size.y; i++)
    {
        for (int j = 0; j < size.x; j++)
        {
            map[i][j] = EMPTY;
            target[i][j] = EMPTY;
        }
    }
    for (int i = 0; i < size.y; i++)
    {
        map[i][0] = map[i][size.x - 1] = EDGE;
        target[i][0] = target[i][size.x - 1] = EDGE;
    }
    for (int i = 0; i < size.x; i++)
    {
        map[0][i] = map[size.y - 1][i] = EDGE;
        target[0][i] = target[size.y - 1][i] = EDGE;
    }
    for (int i = 0; i < RUBBISH_CNT;)
    {
        int temp_x = randomInt(size.x);
        int temp_y = randomInt(size.y);
        if (map[temp_y][temp_x] == 0)
        {
            map[temp_y][temp_x] = RUBBISH;
            target[temp_y][temp_x] = RUBBISH;
            i++;
        }
    }
}
int inline Map::getValue(vec_2i pos)
{
    return target[pos.y][pos.x];
}
int Map::getHash(vec_2i pos)
{
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
int Map::getTarget(vec_2i pos)
{
    return target[pos.y][pos.x];
}
void Map::setTarget(vec_2i pos, int key)
{
    target[pos.y][pos.x] = key;
}
int Map::doAction(vec_2i start, vec_2i offset)
{
    // EDGE : -1(failed)
    // pick : 0(empty)
    // move : 1(succeed)
    vec_2i now = vec_2i(start.x + offset.x, start.y + offset.y);
    int nowVal = getValue(start);
    if (nowVal == EDGE)
    {
        return -1;
    }
    else if (nowVal == RUBBISH)
    {
    }
    else
    {
    }
}

void Map::print(vec_2i pos)
{
    printSucceed("map:\t\t\t\t\t\ttarget:\n");
    for (int i = size.y - 1; i >= 0; i--)
    {
        // for (int i = 0; i < 5; i++) {
        for (int j = 0; j < size.x; j++)
        {
            if (map[i][j] != 0)
            {
                if (map[i][j] == EDGE)
                {
                    printSucceed(map[i][j]);
                }
                else
                {
                    printOk(map[i][j]);
                }
                printSucceed(" ");
            }
            else
            {
                cout << "  ";
            }
        }
        cout << "  ";
        for (int j = 0; j < size.x; j++)
        {
            if (i == pos.y && j == pos.x)
            {
                printError(target[i][j]);
                printError(" ");
            }
            else if (target[i][j] != 0)
            {
                if (map[i][j] == EDGE)
                {
                    printSucceed(map[i][j]);
                }
                else
                {
                    printOk(map[i][j]);
                }
                printSucceed(" ");
            }
            else
            {
                cout << "  ";
            }
        }
        cout << endl;
    }
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
Controller::Controller() {}
