/*================================================================
*  Copyright (C)2019 All rights reserved.
*  FileName : Robbie.cc
*  Author   : elonkou
*  Email    : elonkou@ktime.cc
*  Date     : 2019年10月02日 星期三 11时40分13秒
================================================================*/

#include "Robbie.hh"
#include "Lib.hh"
#include "RobbieConfig.hh"
#include "RobbieMap.hh"
#include <iostream>

using namespace std;

Robbie::Robbie() {
    gene_len   = GENE_LEN;
    str_len    = STR_CNT;
    mutate_all = MUTATE_ALL;
    mutate_val = MUTATE_VAL;
    averScore  = -1000.0;
    score      = 0;
    init();
}
Robbie::~Robbie() {}
void Robbie::init() {
    for (int i = 0; i < gene_len; i++) {
        genes[i] = RandomInt(str_len);
    }
    randomPos();
}
void Robbie::RandomPos() {
    start.x = START_X;
    start.y = START_Y;
    pos     = start;
}
Robbie Robbie::Clone() {
    Robbie r = Robbie();
    for (int i = 0; i < gene_len; i++) {
        r.genes[i] = genes[i];
    }
    return r;
}
void Robbie::Clear() {
    for (int i = 0; i < gene_len; i++) {
        genes[i] = GENE_CLEAR;
    }
}

void Robbie::Print() {
    cout << endl;
    cout << "pos:(" << pos.x << ":" << pos.y << ")\tstart:(" << start.x << ":"
         << start.y << ")"
         << "\tscore:" << GetScore() << endl;
    int next = 81;
    for (int i = 0; i < gene_len; i++) {
        if (i % next == 0 && i != 0) {
            cout << endl;
        }
        cout << genes[i];
    }
    cout << endl;
}

int Robbie::GetScore() { return score; }

void Robbie::Clip(Robbie& other) {
    int pos = RandomInt(gene_len);
    for (int i = 0; i < pos; i++) {
        int temp       = genes[i];
        genes[i]       = other.genes[i];
        other.genes[i] = temp;
    }
}
Robbie Robbie::Clip2(Robbie other, int pos) {
    // change the gene after pos.
    // return the new object.
    Robbie r = Clone();
    for (int i = pos; i < gene_len; i++) {
        r.genes[i] = other.genes[i];
    }
    return r;
}
void Robbie::Clip3(Robbie other) {}

void Robbie::Mutate() {
    for (int i = 0; i < gene_len; i++) {
        int temp = RandomInt(mutate_all);
        if (temp < mutate_val) {
            genes[i] = RandomInt(str_len);
        }
    }
}
void Robbie::Compare(Robbie other) {
    int next = 27;
    for (int i = 0; i < next; i++) {
        if (i < 10) {
            cout << " ";
        }
        PrintSucceed(i);
        printf(" ");
    }
    cout << endl;
    for (int i = 0; i < gene_len; i++) {
        if (i % next == 0 && i != 0) {
            cout << endl;
        }
        if (genes[i] != other.genes[i]) {
            PrintError(genes[i]);
            PrintError(other.genes[i]);
            Printf(" ");
        } else {
            cout << genes[i] << other.genes[i] << " ";
        }
    }
    cout << endl;
}

void Robbie::Play(RobbieMap& map) {
    // map.print(pos);
    for (int i = 0; i < LOOP_CNT; i++) {
        int result = 0;
        int hash   = map.getHash(pos);
        int action = getAction(hash);
        // map.print(pos);
        while (action == RANDOM) {
            action = RandomInt(STR_CNT);
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

void Robbie::PlayOne(int cnt) {
    int res = 0;
    for (int i = 0; i < cnt; i++) {
        RobbieMap mp = RobbieMap();
        play(mp);
        res += getScore();
        score = 0;
    }
    averScore = res * 1.0 / cnt;
}

int Robbie::Move(int action, RobbieMap& map) {
    vec_2i offset = vec_2i(strategy[action].wmove, strategy[action].hmove);
    vec_2i now    = pos + offset;
    int    val    = map.GetValue(now);
    if (val != EDGE) {
        pos = now;
        return action;
    } else {
        score += PUNISHMENT_EDGE;
        return -1;
    }
}

int Robbie::Pick(int action, RobbieMap& map) {
    int val = map.GetValue(pos);
    if (val == RUBBISH) {
        map.SetTarget(pos, EMPTY);
        score += REWARD;
        return action;
    } else {
        score += PUNISHMENT_PICK;
        return -2;
    }
}

int Robbie::GetAction(int hash) { return genes[hash]; }

void Robbie::Save(string fileName) {}

void Robbie::Load(string fileName) {}
