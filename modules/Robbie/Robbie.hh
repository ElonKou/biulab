#pragma once
#ifndef ROBBIE_H_
#define ROBBIE_H_

#include "CoreBase.hh"
#include "RobbieConfig.hh"
#include "SimpleMap.hh"
#include "fstream"
#include <unordered_map>

typedef struct RewardPunishmentInfo {
    int reward;
    int punishment_edge;
    int punishment_pick;
} RewardPunishmentInfo;

class Robbie : public CoreBase {
  public:
    Robbie();
    ~Robbie();
    int                        id;
    int                        father;
    int                        mother;
    int                        str_len;
    int                        gene_len;
    int                        loop_cnt;
    int                        generation;
    int                        mutate_val;
    int                        mutate_all;
    float                      score;
    float                      aver_score;
    vec_2i                     pos;
    vector<int>                genes;
    unordered_map<int, vec_2i> strategy;
    RewardPunishmentInfo*      rp_info;

    Robbie Clip(Robbie mother, int pos = -1);

    void Mutate();

    RobbieActionResult Move(RobbieAction act, SimpleMap& map);

    RobbieActionResult Pick(RobbieAction act, SimpleMap& map);

    RobbieActionResult NextStep(SimpleMap& map);

    void PlaySingleMap(SimpleMap& map);

    void PlayMultiMaps(int cnt);

    void Print();

    void Compare(Robbie other);

    void Save(string save_path);

    void Load(string load_path);
};

#endif