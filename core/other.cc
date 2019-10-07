/*================================================================
*  Copyright (C)2019 All rights reserved.
*  FileName : other.cc
*  Author   : elonkou
*  Email    : elonkou@ktime.cc
*  Date     : 2019年10月05日 星期六 17时59分22秒
================================================================*/

#include "MapConfig.hh"
#include <iostream>
using namespace std;

int main(int argc, char *argv[]){
    MapConfig mc;
    cout << mc.show_dock_sapce << endl;
    cout << mc.show_overlay_bar << endl;
    return 0;
}
