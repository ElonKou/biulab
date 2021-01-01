#pragma once
#ifndef ROBBIE_CONFIG_HH_
#define ROBBIE_CONFIG_HH_

#include <vector>

#define STR_CNT 7       // the length of strategy.
#define GENE_LEN 243    // the length of genes.
#define MUTATE_ALL 1000 // mutate all.
#define MUTATE_VAL 5    // mutate rate = MUTATE_VAL/MUTATE_ALL.
#define CLIP_CNT 1      // mutate cut times.

#define LOOP_MAP 10           // for play multi maps.
#define LOOP_CNT 200          // for play steps.
#define ROBBIE_CNT 200        // how many robiies in one generations.
#define LOOP_CONTROLLER 10000 // the count of generations.

#define PUNISHMENT_EDGE -5 // punishment for move to edge of map.
#define PUNISHMENT_PICK -1 // punishment for pick empty place.
#define REWARD_PICK 10     // reward for right pick.

typedef enum RobbieAction { ACTION_UP,
                            ACTION_DOWN,
                            ACTION_RIGHT,
                            ACTION_LEFT,
                            ACTION_RANDOM,
                            ACTION_WAIT,
                            ACTION_PICK } RobbieAction;

typedef enum RobbieActionResult {
    AC_RES_OK,
    AC_RES_PUNISHMENT_EDGE,
    AC_RES_PUNISHMENT_PICK,
    AC_RES_REWARD_RUBBISH
} RobbieActionResult;

typedef struct RobbieActionHistory {
    vector<int>                hashs;
    vector<vec_2i>             positions;
    vector<RobbieAction>       actions;
    vector<RobbieActionResult> results;
} RobbieActionHistory;

#endif