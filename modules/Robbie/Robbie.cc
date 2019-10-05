/*================================================================
*  Copyright (C)2019 All rights reserved.
*  FileName : Robbie.cc
*  Author   : elonkou
*  Email    : elonkou@ktime.cc
*  Date     : 2019年10月02日 星期三 11时40分13秒
================================================================*/

#include "Robbie.hh"
#include <iostream>
#include "Lib.hh"
#include "RobbieConfig.hh"
#include "RobbieMap.hh"

using namespace std;

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

void Robbie::play(RobbieMap &map) {
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
        // cout << "=" << result << " ";
        // cout << "=" << action << " ";
    }
    // cout << endl << score << endl;
    // map.cleanTarget();
}

void Robbie::playOne(int cnt) {
    int res = 0;
    for (int i = 0; i < cnt; i++) {
        RobbieMap mp = RobbieMap();
        play(mp);
        res += getScore();
        score = 0;
    }
    averScore = res * 1.0 / cnt;
}

int Robbie::move(int action, RobbieMap &map) {
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

int Robbie::pick(int action, RobbieMap &map) {
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
