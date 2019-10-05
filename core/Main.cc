/*================================================================
*  Copyright (C)2019 All rights reserved.
*  FileName : Main.cc
*  Author   : elonkou
*  Email    : elonkou@ktime.cc
*  Date     : 2019年10月02日 星期三 11时40分13秒
================================================================*/
#include "Main.hh"
#include <iostream>
#include <string>
#include <vector>
#include "Frame.hh"
using namespace std;


int main() {
    windowView view;
    Controller con;
    view.setController(&con);
    view.startWindow();
    return 0;
}
