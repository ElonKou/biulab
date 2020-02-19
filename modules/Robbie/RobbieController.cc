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

void RobbieControllerData::UpdateData() {
    dis_map = GetData<SimpleMap>("SimpleMap", "RobbieController");
}

RobbieController::RobbieController()
    : save_run(false)
    , running(false)
    , pause(false)
    , stoped(false)
    , play_chanegd(false)
    , run_step(false) {
    data                   = new RobbieControllerData();
    data->loop_controller  = LOOP_CONTROLLER;
    data->loop_map         = LOOP_MAP;
    data->robbie_cnt       = ROBBIE_CNT;
    data->mutate_rate      = MUTATE_VAL * 1.0 / MUTATE_ALL;
    data->global_id        = 0;
    data->speed            = 4;
    data->train_stop_check = false;
    data->max_histyory     = -1000.0;
    data->dis_map          = NULL;
    data->dis_rob          = new Robbie();
    data->dis_rob->Load(BIULAB_APPLICATION_PATH "/genetic/robbies/0_487.txt");
    data->dis_rob->pos = vec_2i(2, 2);
    // string default_robbie_path = "~/ELONKOU/03.GENETIC/genetic/results";
    // string default_robbie_name = "std.rob";
    // string default_map_path    = "~/ELONKOU/03.GENETIC/genetic/maps";
    // string default_map_name    = "std.map";
    // strcpy(robbie_path, default_robbie_path.c_str());
    // strcpy(robbie_name, default_robbie_name.c_str());
    // strcpy(map_path, default_map_path.c_str());
    // strcpy(map_name, default_map_name.c_str());
    Init();
}

RobbieController::~RobbieController() {}

void RobbieController::Init() {
    for (int i = 0; i < data->robbie_cnt; i++) {
        Robbie rob     = Robbie();
        rob.id         = data->global_id++;
        rob.pos        = vec_2i(1, 1);
        rob.generation = 0;
        data->robbies.push_back(rob);
    }
}

void RobbieController::Train() {
    for (int k = 0; k < data->loop_controller; k++) {
        vector<Robbie> robbies_temp;
        for (int i = 0; i < data->robbie_cnt; i++) {
            data->robbies[i].PlayMultiMaps(data->loop_map);
            data->robbie_scores[i].aver_score    = data->robbies[i].aver_score;
            data->robbie_scores_tf[i].aver_score = data->robbies[i].aver_score;
            if (k < 1000) {
                if (data->robbie_scores_tf[i].aver_score < -500) {
                    data->robbie_scores_tf[i].aver_score = -500;
                }
                data->robbie_scores_tf[i].aver_score = pow(500 + data->robbie_scores_tf[i].aver_score, 3.0) * 0.000001;
            } else {
                if (data->robbie_scores_tf[i].aver_score < 0) {
                    data->robbie_scores_tf[i].aver_score = 0;
                } else {
                    data->robbie_scores_tf[i].aver_score = data->robbie_scores_tf[i].aver_score * 50;
                    // scores_tf[i] = scores_tf[i] * 50 * 1.3;
                    // scores_tf[i] = pow(scores_tf[i], 1.3);
                }
            }
        }

        int top_id = ShowHisgram(k);
        // if (data->max_histyory < data->robbie_scores[top_id].aver_score) {
        //     data->max_histyory = data->robbie_scores[top_id].aver_score;
        //     data->robbies[top_id].Print();
        //     SaveRobbie(data->robbies[top_id], robbie_path);
        // }
        data->robbies[top_id].Compare(data->robbies[0]);

        float sum = 0.0;
        for (size_t i = 0; i = data->robbie_scores_tf.size(); i++) {
            sum += data->robbie_scores_tf[i].aver_score;
        }
        for (int i = 0; i < data->robbie_cnt; i++) {
            data->robbie_scores_tf[i].aver_score /= sum;
            if (i != 0) {
                data->robbie_scores_tf[i].aver_score = data->robbie_scores_tf[i].aver_score + data->robbie_scores_tf[i - 1].aver_score;
            }
        }
        cout << "================================================================================" << endl;
        for (int i = 0; i < data->robbie_cnt / 2; i++) {
            int fa  = GetIndex(RandomFloat());
            int mo  = GetIndex(RandomFloat());
            int pos = RandomInt(GENE_LEN);
            robbies_temp.push_back(data->robbies[fa].Clip(data->robbies[mo], pos));
            robbies_temp.push_back(data->robbies[mo].Clip(data->robbies[fa], pos));
        }
        data->robbies.clear();
        data->robbie_scores.clear();
        data->robbie_scores_tf.clear();
        for (int i = 0; i < data->robbie_cnt; i++) {
            data->robbies.push_back(robbies_temp[i]);
            data->robbies[i].Mutate();
        }
    }
}

void RobbieController::Print_str() {
    cout << "   0  " << endl;
    cout << " 3 4 2" << endl;
    cout << "   1  " << endl;
}

void RobbieController::Play() {
    // display target in map.
    vector<TargetElem> render_targets;
    TargetElem         robbies;
    robbies.positions.push_back(data->dis_rob->pos);
    robbies.p_type = PATH_ACTOR;
    render_targets.push_back(robbies);
    // display paths in map.
    TargetElem paths;
    paths.positions = data->history.positions;
    for (auto idx = data->history.positions.rbegin(); idx != data->history.positions.rend(); idx++) {
        paths.positions.push_back(*idx);
    }
    reverse(paths.positions.begin(), paths.positions.end());
    paths.p_type = PATH_HISTORY;
    render_targets.push_back(paths);
    data->dis_map->SetRenderTargets(render_targets);

    int          hash    = data->dis_map->GetHash(data->dis_rob->pos);
    RobbieAction pre_act = RobbieAction(data->dis_rob->genes[hash]);
    data->history.hashs.push_back(hash);
    data->history.positions.push_back(data->dis_rob->pos);
    data->history.actions.push_back(pre_act);
    data->history.results.push_back(data->dis_rob->NextStep(*(data->dis_map)));
    // map.CleanTarget()
    if (data->history.hashs.size() > 20) {
        data->history.hashs.erase(data->history.hashs.begin());
        data->history.positions.erase(data->history.positions.begin());
        data->history.actions.erase(data->history.actions.begin());
        data->history.results.erase(data->history.results.begin());
    }
}

void RobbieController::UpdateInFrame() {
    static int frame_rate = 0;
    int        max        = 60 / data->speed;
    if (running) {
        if (!pause) {
            frame_rate++;
            if (frame_rate > max) {
                frame_rate = 0;
                Play();
            }
        }
    }
    if (play_chanegd && stoped) {
        data->dis_map->CleanTarget();
        data->dis_rob->pos        = vec_2i(2, 2);
        data->dis_rob->score      = 0;
        data->dis_rob->aver_score = -1000.0;
        play_chanegd              = false;
        stoped                    = false;
    }
}

Robbie RobbieController::LoadRobbie(string robbie_path) {
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
void RobbieController::SaveRobbie(Robbie& rob, string robbie_path) {
    int score = int(rob.aver_score);
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

int RobbieController::GetIndex(float random_index) {
    int i = 0;
    while (data->robbie_scores_tf[i].aver_score < random_index) {
        i++;
    }
    return i;
}

int RobbieController::ShowHisgram(int num) {
    int   minIndex = 0;
    int   maxIndex = 0;
    float minData  = 1000;
    float maxData  = -1000;
    float sum      = 0.0;
    int   nevCnt   = 0;
    for (int i = 0; i < ROBBIE_CNT; i++) {
        sum += data->robbie_scores[i].aver_score;
        if (data->robbie_scores[i].aver_score > 0) {
            nevCnt++;
        }
        if (data->robbie_scores[i].aver_score > maxData) {
            maxIndex = i;
            maxData  = data->robbie_scores[i].aver_score;
        }
        if (data->robbie_scores[i].aver_score < minData) {
            minIndex = i;
            minData  = data->robbie_scores[i].aver_score;
        }
    }
    int   clipCnt        = 20;
    float res            = (maxData - minData) * 1.0;
    float step           = res / clipCnt;
    int   shows[clipCnt] = {0};
    for (int i = 0; i < ROBBIE_CNT; i++) {
        int index = int((data->robbie_scores[i].aver_score - minData) / step);
        shows[index]++;
    }
    cout << num << "\tID:" << maxIndex << "\tCLIP_CNT:" << clipCnt
         << "\tSTEP:" << step << "\tAVER:" << setw(5) << setprecision(5)
         << sum / ROBBIE_CNT << "\t>=0:" << nevCnt << "\tMIN:" << minData
         << "\tMAX:" << maxData << "\tHIS_MAX:" << data->max_histyory << endl;
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

void RobbieController::UpdateData() {
    data->UpdateData();
}