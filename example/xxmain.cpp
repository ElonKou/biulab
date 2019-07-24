//++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// File   :test.cpp
// Author :elonkou
// E-mail :elonkou@ktime.cc
// Date   :Tue 22 Jan 2019 05:49:23 PM CST
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#include "xx.hpp"
using namespace std;

int main() {
    // string robbie_path =
    //     "/home/elonkou/ELONKOU/03.GENETIC/genetic/results/0_487.txt";
    string save_path = "/home/elonkou/ELONKOU/03.GENETIC/genetic/results/1_";
    Controller con = Controller(save_path);
    con.train();
    // Robbie rob = con.loadRobbie(robbie_path);
    // Robbie rob;
    // rob.print();
    // Robbie rob = Robbie();
    // Map mp = Map();
    // mp.print(rob.start);
    // con.playScreen(rob, mp);
    // con.print_str();
    // rob.play(mp);
    // mp.print(rob.pos);
    return 0;
}