/*================================================================
*  Copyright (C)2019 All rights reserved.
*  FileName : Lab.cc
*  Author   : elonkou
*  Email    : elonkou@ktime.cc
*  Date     : 2019年10月05日 星期六 16时12分13秒
================================================================*/

#include "Lab.hh"
#include <iostream>

using namespace std;

Lab::Lab() { InitLab(); }

Lab::~Lab() {}

void Lab::InitLab() {
    root    = "/home/elonkou/ELONKOU/03.GENETIC/genetic";
    version = 0;
}

void Lab::Start() {
    cout << "biulab is running." << endl;
    window.StartWindow();
}
