#pragma once
#ifndef ROBBIE_CONTROLLER_H_
#define ROBBIE_CONTROLLER_H_

#include "BiuLabTypes.hh"
#include "Robbie.hh"
#include "RobbieConfig.hh"
#include "SimpleMap.hh"
#include <string>
using namespace std;

class RobbieController {
  public:
    struct Result {
        int score;
        int robbie_id;
        int map_id;
    };
    RobbieController();
    RobbieController(string save_path);
    ~RobbieController();
    int   loop_controller;
    int   loop_map;
    int   robbie_cnt;
    float mutate_rate;
    float max_histyory;
    char  robbie_path[255];
    char  robbie_name[255];
    char  map_path[255];
    char  map_name[128];
    // Map map;
    int map_width;
    int map_height;
    // run
    bool save_run;
    bool running;
    bool chanegd;
    bool run_step;

    Robbie robbies[ROBBIE_CNT];
    Robbie robbies_temp[ROBBIE_CNT];
    float  scores[ROBBIE_CNT];
    float  scores_tf[ROBBIE_CNT];
    // void play(Robbie r, Map &m);

    void Init();

    void Train();

    void Print_str();

    void PlayScreen(Robbie& rob, RobbieMap& map);

    Robbie LoadRobbie(string robbie_path);

    void SaveRobbie(Robbie& rob, string robbie_path);

    void AddRobbie();

    void SetMap(RobbieMap* map);

    int ShowHisgram(int num);

    int GetIndex(float random_index);

    void PlayOne();
};

#endif