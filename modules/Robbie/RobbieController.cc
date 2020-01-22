/*================================================================
*  Copyright (C)2019 All rights reserved.
*  FileName : RobbieController.cc
*  Author   : elonkou
*  Email    : elonkou@ktime.cc
*  Date     : 2019年10月02日 星期三 11时44分45秒
================================================================*/

#include "RobbieController.hh"
#include "Lib.hh"
#include "Robbie.hh"
#include <algorithm>
#include <cmath>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <iostream>
using namespace std;

RobbieController::RobbieController()
    : loop_controller(LOOP_CONTROLLER)
    , loop_map(LOOP_MAP)
    , robbie_cnt(ROBBIE_CNT)
    , mutate_rate(MUTATE_VAL * 1.0 / MUTATE_ALL)
    , max_histyory(-1000.0)
    , map_width(MAP_WIDTH)
    , map_height(MAP_HEIGHT)
    , save_run(false)
    , running(false)
    , chanegd(false)
    , run_step(false) {
    string default_robbie_path = "~/ELONKOU/03.GENETIC/genetic/results";
    string default_robbie_name = "robbie.rob";
    string default_map_path    = "~/ELONKOU/03.GENETIC/genetic/maps";
    string default_map_name    = "some.map";
    strcpy(robbie_path, default_robbie_path.c_str());
    strcpy(robbie_name, default_robbie_name.c_str());
    strcpy(map_path, default_map_path.c_str());
    strcpy(map_name, default_map_name.c_str());
}
RobbieController::RobbieController(string save_p) {
    RobbieController();
    strcpy(robbie_path, save_p.c_str());
}
RobbieController::~RobbieController() {}

void RobbieController::init() {
    // init controller
    float res[robbie_cnt];
    float res_ori[robbie_cnt];
    for (int i = 0; i < robbie_cnt; i++) {
        robbies[i]   = Robbie();
        scores[i]    = 0.0;
        scores_tf[i] = 0.0;
    }
}

void RobbieController::train() {
    for (int k = 0; k < loop_controller; k++) {
        for (int i = 0; i < robbie_cnt; i++) {
            robbies[i].playOne(loop_map);
            scores[i]    = robbies[i].averScore;
            scores_tf[i] = robbies[i].averScore;
            if (k < 1000) {
                if (scores_tf[i] < -500) {
                    scores_tf[i] = -500;
                }
                scores_tf[i] = pow(500 + scores_tf[i], 3.0) * 0.000001;
            } else {
                if (scores_tf[i] < 0) {
                    scores_tf[i] = 0;
                } else {
                    scores_tf[i] = scores_tf[i] * 50;
                    // scores_tf[i] = scores_tf[i] * 50 * 1.3;
                    // scores_tf[i] = pow(scores_tf[i], 1.3);
                }
            }
        }

        int top_id = showHisgram(k);
        if (max_histyory < scores[top_id]) {
            max_histyory = scores[top_id];
            robbies[top_id].print();
            saveRobbie(robbies[top_id], robbie_path);
        }
        robbies[top_id].compare(robbies[0]);

        float all = accumulate(scores_tf, scores_tf + ROBBIE_CNT, 0.0);
        for (int i = 0; i < ROBBIE_CNT; i++) {
            scores_tf[i] /= all;
            if (i != 0) {
                scores_tf[i] = scores_tf[i] + scores_tf[i - 1];
            }
        }
        cout << "========================================"
                "========================================"
             << endl;
        for (int i = 0; i < ROBBIE_CNT / 2; i++) {
            int fa                  = getIndex(randomFloat());
            int mo                  = getIndex(randomFloat());
            int pos                 = randomInt(GENE_LEN);
            robbies_temp[i * 2]     = robbies[fa].clip2(robbies[mo], pos);
            robbies_temp[i * 2 + 1] = robbies[mo].clip2(robbies[fa], pos);
        }
        for (int i = 0; i < ROBBIE_CNT; i++) {
            robbies[i] = robbies_temp[i];
            robbies[i].mutate();
        }
    }
}

void RobbieController::print_str() {
    cout << "   0  " << endl;
    cout << " 3 4 2" << endl;
    cout << "   1  " << endl;
}

void RobbieController::playScreen(Robbie& rob, RobbieMap& map) {
    PlayActions act;
    for (int i = 0; i < LOOP_CNT; i++) {
        print_str();
        int result = 0;
        int hash   = map.getHash(rob.pos);
        int action = rob.getAction(hash);
        usleep(100000);
        act.hash         = hash;
        act.actions[i]   = action;
        act.positions[i] = rob.pos;
        map.drawFrame(act, rob.genes);
        cout << i << " : " << rob.score << "hash:" << hash << endl;
        while (action == RANDOM) {
            action = randomInt(STR_CNT);
        }
        switch (action) {
        case WAIT:
            break;
        case PICK:
            result = rob.pick(action, map);
            break;
        default:
            result = rob.move(action, map);
            break;
        }
        // cout << "=" << result << " ";
        // cout << "=" << action << " ";
    }
    // cout << endl << score << endl;
    // map.cleanTarget();
}

Robbie RobbieController::loadRobbie(string robbie_path) {
    Robbie   rob;
    ifstream fp;
    fp.open(robbie_path);
    string data;
    string ss;
    while (getline(fp, ss)) {
        data += ss;
    }
    for (int i = 0; i < data.size(); i++) {
        rob.genes[i] = int(data[i] - '0');
    }
    fp.close();
    return rob;
}
void RobbieController::saveRobbie(Robbie& rob, string robbie_path) {
    int score = int(rob.averScore);
    if (robbie_path != "") {
        robbie_path += to_string(score) + ".txt";
        ofstream fp;
        fp.open(robbie_path);
        for (int i = 0; i < rob.gene_len; i++) {
            if (i % 81 == 0 && i != 0) {
                fp << "\n";
            }
            fp << rob.genes[i];
        }
        fp.close();
        cout << robbie_path << " saved." << endl;
    }
}

int RobbieController::getIndex(float random_index) {
    int i = 0;
    while (scores_tf[i] < random_index) {
        i++;
    }
    return i;
}

int RobbieController::showHisgram(int num) {
    int   minIndex = 0;
    int   maxIndex = 0;
    float minData  = 1000;
    float maxData  = -1000;
    float sum      = 0.0;
    int   nevCnt   = 0;
    for (int i = 0; i < ROBBIE_CNT; i++) {
        sum += scores[i];
        if (scores[i] > 0) {
            nevCnt++;
        }
        if (scores[i] > maxData) {
            maxIndex = i;
            maxData  = scores[i];
        }
        if (scores[i] < minData) {
            minIndex = i;
            minData  = scores[i];
        }
    }
    int   clipCnt        = 20;
    float res            = (maxData - minData) * 1.0;
    float step           = res / clipCnt;
    int   shows[clipCnt] = {0};
    for (int i = 0; i < ROBBIE_CNT; i++) {
        int index = int((scores[i] - minData) / step);
        shows[index]++;
    }
    cout << num << "\tID:" << maxIndex << "\tCLIP_CNT:" << clipCnt
         << "\tSTEP:" << step << "\tAVER:" << setw(5) << setprecision(5)
         << sum / ROBBIE_CNT << "\t>=0:" << nevCnt << "\tMIN:" << minData
         << "\tMAX:" << maxData << "\tHIS_MAX:" << max_histyory << endl;
    for (int i = 0; i < clipCnt; i++) {
        cout << left << setw(9) << minData + i * step << right << setw(9)
             << minData + (i + 1) * step << ":";
        for (int j = 0; j < shows[i]; j++) {
            cout << "*";
        }
        cout << endl;
    }
    return maxIndex;
}