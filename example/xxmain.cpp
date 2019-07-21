//++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// File   :test.cpp
// Author :elonkou
// E-mail :elonkou@ktime.cc
// Date   :Tue 22 Jan 2019 05:49:23 PM CST
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#include <algorithm>
#include <numeric>
#include <iostream>
#include "xx.hpp"
using namespace std;

int getIndex(float res[], float score)
{
    int i = 0;
    while (res[i] < score)
    {
        i++;
    }
    return i;
}

void print_str()
{
    std::cout << "   0  " << endl;
    std::cout << " 3 4 2" << endl;
    std::cout << "   1  " << endl;
}

int main()
{
    print_str();
    Robbie robs[ROBBIE_CNT];
    Robbie temp[ROBBIE_CNT];
    float res[ROBBIE_CNT];
    for (int i = 0; i < ROBBIE_CNT; i++)
    {
        robs[i] = Robbie();
    }
    for (int k = 0; k < 1000; k++)
    {
        for (int i = 0; i < ROBBIE_CNT; i++)
        {
            res[i] = robs[i].playOne();
            res[i] += 5 * LOOP_CNT;
            // res[i] = pow(res[i], 2);
        }
        float top = (*max_element(res, res + ROBBIE_CNT));
        float bot = (*min_element(res, res + ROBBIE_CNT));
        float all = accumulate(res, res + ROBBIE_CNT, 0.0);
        std::cout << k << ": top:" << top << " aver:" << all / ROBBIE_CNT;
        // for (int i = 0; i < ROBBIE_CNT; i++) {
        //     std::cout << res[i] << " ";
        // }
        for (int i = 0; i < ROBBIE_CNT; i++)
        {
            res[i] /= all;
            if (i != 0)
            {
                res[i] = res[i] + res[i - 1];
            }
            // cout << " " << res[i];
        }
        std::cout << endl
                  << "++++++++++++++++++++++++++++++++++" << endl;
        for (int i = 0; i < ROBBIE_CNT / 2; i++)
        {
            int fa = getIndex(res, randomFloat());
            int mo = getIndex(res, randomFloat());
            int pos = randomInt(GENE_LEN);
            temp[i * 2] = robs[fa].clip2(robs[mo], pos);
            temp[i * 2 + 1] = robs[mo].clip2(robs[fa], pos);
        }
        for (int i = 0; i < ROBBIE_CNT; i++)
        {
            robs[i] = temp[i];
            robs[i].mutate();
        }
        robs[0].compare(robs[100]);
    }

    // Controller con = Controller();
    // Robbie rob = Robbie();
    // Map mp = Map();
    // rob.play(mp);
    return 0;
}
