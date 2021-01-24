/*================================================================
*  Copyright (C)2019 All rights reserved.
*  FileName : Main.cc
*  Author   : elonkou
*  Email    : elonkou@ktime.cc
*  Date     : 2019年10月02日 星期三 11时40分13秒
================================================================*/

#include "Lab.hh"

int main(int argc, char* argv[]) {
    Lab lab;
    lab.InitLab();
    cout << "biulab is running." << endl;
    lab.Run();
    cout << "biulab is terminated." << endl;
    return 0;
}
