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
#include "SimpleMap.hh"
#include <iostream>

using namespace std;

Robbie::Robbie() {
    id                       = -1;
    father                   = -1;
    mother                   = -1;
    gene_len                 = GENE_LEN;
    str_len                  = STR_CNT;
    loop_cnt                 = LOOP_CNT;
    generation               = -1;
    mutate_val               = MUTATE_VAL;
    mutate_all               = MUTATE_ALL;
    score                    = 0;
    aver_score               = -1000.0;
    pos                      = vec_2i(1, 1);
    rp_info                  = new RewardPunishmentInfo();
    rp_info->reward          = REWARD_PICK;
    rp_info->punishment_edge = PUNISHMENT_EDGE;
    rp_info->punishment_pick = PUNISHMENT_PICK;
    strategy.insert({0, {0, 1}});
    strategy.insert({1, {0, -1}});
    strategy.insert({2, {1, 0}});
    strategy.insert({3, {-1, 0}});
    strategy.insert({4, {0, 0}});
    strategy.insert({5, {0, 0}});
    strategy.insert({6, {0, 0}});
    for (int i = 0; i < gene_len; i++) {
        genes.push_back(RandomInt(str_len));
    }
}

Robbie::~Robbie() {}

Robbie Robbie::Clip(Robbie mother, int pos) {
    Robbie rob;
    rob.father     = id;
    rob.mother     = mother.id;
    rob.generation = MAX(generation, mother.generation) + 1;
    if (pos == -1) {
        int pos = RandomInt(gene_len);
    }
    for (int i = 0; i < pos; i++) {
        rob.genes.push_back(genes[i]);
    }
    for (int i = pos; i < gene_len; i++) {
        rob.genes.push_back(mother.genes[i]);
    }
    return rob;
}

void Robbie::Mutate() {
    for (int i = 0; i < gene_len; i++) {
        int temp = RandomInt(mutate_all);
        if (temp < mutate_val) {
            genes[i] = RandomInt(str_len);
        }
    }
}

RobbieActionResult Robbie::NextStep(SimpleMap& map) {
    RobbieActionResult result;
    int                hash = map.GetHash(pos);
    RobbieAction       act  = RobbieAction(genes[hash]);
    while (act == ACTION_RANDOM) {
        act = RobbieAction(RandomInt(str_len));
    }
    switch (act) {
    case ACTION_WAIT:
        break;
    case ACTION_PICK:
        result = Pick(act, map);
        break;
    default:
        result = Move(act, map);
        break;
    }
    return result;
}

void Robbie::PlaySingleMap(SimpleMap& map) {
    score      = 0;
    aver_score = 0.0;
    for (int i = 0; i < loop_cnt; i++) {
        int result = NextStep(map);
    }
}

void Robbie::PlayMultiMaps(int cnt) {
    int res    = 0;
    score      = 0;
    aver_score = 0.0;
    for (int i = 0; i < cnt; i++) {
        SimpleMap mp = SimpleMap();
        // mp.Init();
        PlaySingleMap(mp);
        res += score;
        score = 0;
    }
    aver_score = res * 1.0 / cnt;
}

RobbieActionResult Robbie::Move(RobbieAction act, SimpleMap& map) {
    vec_2i now = pos + strategy[int(act)];
    int    val = map.GetValue(now);
    if (val != MAP_EDGE) {
        pos = now;
        return AC_RES_OK;
    } else {
        score += rp_info->punishment_edge;
        return AC_RES_PUNISHMENT_EDGE;
    }
}

RobbieActionResult Robbie::Pick(RobbieAction act, SimpleMap& map) {
    int val = map.GetValue(pos);
    if (val == MAP_RUBBISH) {
        map.SetTarget(pos, MAP_EMPTY);
        score += rp_info->reward;
        return AC_RES_REWARD_RUBBISH;
    } else {
        score += rp_info->punishment_pick;
        return AC_RES_PUNISHMENT_PICK;
    }
}

void Robbie::Print() {
    cout << endl;
    cout << "pos:(" << pos.x << ":" << pos.y << ")"
         << "\tscore:" << score << endl;
    int next = 81;
    for (int i = 0; i < gene_len; i++) {
        if (i % next == 0 && i != 0) {
            cout << endl;
        }
        cout << genes[i];
    }
    cout << endl;
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
            printf(" ");
        } else {
            cout << genes[i] << other.genes[i] << " ";
        }
    }
    cout << endl;
}
void Robbie::Save(string save_path) {}

void Robbie::Load(string load_path) {
    ifstream fp;
    fp.open(load_path);
    string data;
    string ss;
    while (getline(fp, ss)) {
        data += ss;
    }
    for (int i = 0; i < data.size(); i++) {
        genes[i] = int(data[i] - '0');
    }
    fp.close();
}
