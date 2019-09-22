//++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// File   :main.cpp
// Author :elonkou
// E-mail :elonkou@ktime.cc
// Date   :Mon 07 Jan 2019 05:33:32 PM CST
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#include "main.hh"
#include <iostream>
#include <string>
#include <vector>
#include "core.hh"
#include "frame.hh"
using namespace std;

int main() {
    windowView view;
    Controller con;
    view.setController(&con);

    // string rob_p =
    // "/home/elonkou/ELONKOU/03.GENETIC/genetic/results/0_487.txt"; Robbie rob
    // = con.loadRobbie(rob_p); con.playScreen(rob, mp); con.loop();
    // con.print();

    // string robbie_path =
    //     "/home/elonkou/ELONKOU/03.GENETIC/genetic/results/0_487.txt";
    // Controller con = Controller();
    // con.train();
    // Robbie rob = con.loadRobbie(robbie_path);
    // Robbie rob;
    // rob.print();
    // Robbie rob = Robbie();
    // Map mp = Map();
    // mp.print(rob.start);
    // con.playScreen(rob, mp);

    view.startWindow();
    return 0;
}

// int main() {
//     string robbie_path =
//         "/home/elonkou/ELONKOU/03.GENETIC/genetic/results/0_487.txt";
//     Controller con = Controller();
//     // con.train();
//     Robbie rob = con.loadRobbie(robbie_path);
//     // Robbie rob;
//     // rob.print();
//     // Robbie rob = Robbie();
//     Map mp = Map();
//     // mp.print(rob.start);
//     con.playScreen(rob, mp);
//     // rob.play(mp);
//     // mp.print(rob.pos);
//     return 0;
// }