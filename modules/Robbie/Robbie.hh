#pragma once
#ifndef ROBBIE_H_
#define ROBBIE_H_

#include "RobbieConfig.hh"
#include "RobbieMap.hh"
#include "BiuTypes.hh"

class Robbie {
   public:
    Robbie();
    ~Robbie();
    Robbie clone();
    // gene
    Strategy strategy[STR_CNT] = {{0, 0, 1}, {1, 0, -1}, {2, 1, 0}, {3, -1, 0},
                                  {4, 0, 0}, {5, 0, 0},  {6, 0, 0}};
    int gene_len;
    int str_len;
    int genes[GENE_LEN];
    int mutate_all;
    int mutate_val;

    void init();
    void randomPos();
    void clear();
    void clip(Robbie &other);
    Robbie clip2(Robbie other, int pos);
    void clip3(Robbie other);
    void mutate();
    void compare(Robbie other);
    int move(int action, RobbieMap &map);
    int pick(int action, RobbieMap &map);
    void play(RobbieMap &map);
    void playOne(int cnt);
    void print();
    int getScore();
    int getAction(int hash);
    void save(string fileName);
    void load(string fileName);
    // robbie info
    int id;
    int score;
    int generation;
    int parentId[PARENT_CNT];
    float averScore;
    vec_2i pos;
    vec_2i start;
};

#endif