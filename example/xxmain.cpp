//++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// File   :test.cpp
// Author :elonkou
// E-mail :elonkou@ktime.cc
// Date   :Tue 22 Jan 2019 05:49:23 PM CST
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#include <algorithm>
#include <cmath>
#include <iostream>
#include <numeric>
#include "xx.hpp"
using namespace std;

int getIndex(float res[], float score) {
    int i = 0;
    while (res[i] < score) {
        i++;
    }
    return i;
}

void print_str() {
    std::cout << "   0  " << endl;
    std::cout << " 3 4 2" << endl;
    std::cout << "   1  " << endl;
}

int main() {
    // print_str();
    float max_score = -1000;
    Robbie robs[ROBBIE_CNT];
    Robbie temp[ROBBIE_CNT];
    float res[ROBBIE_CNT];
    float res_ori[ROBBIE_CNT];
    for (int i = 0; i < ROBBIE_CNT; i++) {
        robs[i] = Robbie();
    }
    for (int k = 0; k < 5000; k++) {
        for (int i = 0; i < ROBBIE_CNT; i++) {
            robs[i].playOne();
            res_ori[i] = robs[i].averScore;
            res[i] = robs[i].averScore;
            if (k < LOOP_CONTROLLER) {
                if (res[i] < -500) {
                    res[i] = -500;
                }
                res[i] = pow(500 + res[i], 3.0) * 0.000001;
            } else {
                if (res[i] < 0) {
                    res[i] = 0;
                } else {
                    float xx = res[i] * 50;
                    res[i] = xx;
                }
            }

            // cout << res_ori[i] << " ";
            // cout << res_ori[i] << ":" << res[i] << " ";
            // res[i] = pow(res[i], 2);
        }
        int top_id = distance(
            res_ori, max_element(res_ori, res_ori + sizeof(res_ori) /
                                                        sizeof(res_ori[0])));
        float top = (*max_element(res_ori, res_ori + ROBBIE_CNT));
        float bot = (*min_element(res_ori, res_ori + ROBBIE_CNT));
        float all_ori = accumulate(res_ori, res_ori + ROBBIE_CNT, 0.0);

        std::cout << k << " top_id:" << top_id << " top:" << res_ori[top_id]
                  << " aver:" << all_ori / ROBBIE_CNT << endl;
        if (max_score < res_ori[top_id]) {
            max_score = res_ori[top_id];
            robs[top_id].print();
        }
        robs[top_id].compare(robs[100]);

        float all = accumulate(res, res + ROBBIE_CNT, 0.0);
        // for (int i = 0; i < ROBBIE_CNT; i++) {
        //     std::cout << res[i] << " ";
        // }
        for (int i = 0; i < ROBBIE_CNT; i++) {
            res[i] /= all;
            if (i != 0) {
                res[i] = res[i] + res[i - 1];
            }
            // cout << " " << res[i];
        }
        std::cout << endl << "++++++++++++++++++++++++++++++++++" << endl;
        for (int i = 0; i < ROBBIE_CNT / 2; i++) {
            int fa = getIndex(res, randomFloat());
            int mo = getIndex(res, randomFloat());
            int pos = randomInt(GENE_LEN);
            temp[i * 2] = robs[fa].clip2(robs[mo], pos);
            temp[i * 2 + 1] = robs[mo].clip2(robs[fa], pos);
        }
        for (int i = 0; i < ROBBIE_CNT; i++) {
            robs[i] = temp[i];
            robs[i].mutate();
        }
        // robs[0].compare(robs[100]);
    }

    // Controller con = Controller();
    // Robbie rob = Robbie();
    // Map mp = Map();
    // rob.play(mp);
    return 0;
}
