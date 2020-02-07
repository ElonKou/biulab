#pragma once
#ifndef ROBBIE_H_
#define ROBBIE_H_

#include "BiuLabTypes.hh"
#include "RobbieConfig.hh"
#include "RobbieMap.hh"

class Robbie {
  public:
    Robbie();
    ~Robbie();
    Robbie clone();
    // gene
    Strategy strategy[STR_CNT] = {{0, 0, 1}, {1, 0, -1}, {2, 1, 0}, {3, -1, 0}, {4, 0, 0}, {5, 0, 0}, {6, 0, 0}};
    int      gene_len;
    int      str_len;
    int      genes[GENE_LEN];
    int      mutate_all;
    int      mutate_val;

    // robbie info
    int    id;
    int    score;
    int    generation;
    int    parentId[PARENT_CNT];
    float  averScore;
    vec_2i pos;
    vec_2i start;

    void Init();

    void   RandomPos();
    
    void   Clear();
    
    void   Clip(Robbie& other);
    
    Robbie Clip2(Robbie other, int pos);
    
    void   Clip3(Robbie other);
    
    void   Mutate();
    
    void   Compare(Robbie other);
    
    int    Move(int action, RobbieMap& map);
    
    int    Pick(int action, RobbieMap& map);
    
    void   Play(RobbieMap& map);
    
    void   PlayOne(int cnt);
    
    void   Print();
    
    int    GetScore();
    
    int    GetAction(int hash);
    
    void   Save(string fileName);
    
    void   Load(string fileName);
};

#endif