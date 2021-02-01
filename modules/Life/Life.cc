/*================================================================
*  Copyright (C)2020 All rights reserved.
*  FileName : Life.cc
*  Author   : elonkou
*  Email    : elonkou@ktime.cc
*  Date     : Mon 01 Feb 2021 05:03:23 PM CST
================================================================*/

#include "Life.hh"
#include "Lib.hh"
#include <iostream>

Life::Life() {
    width  = 128;
    height = 64;
    map    = new int*[height];
    temp   = new int*[height];

    for (int i = 0; i < height; i++) {
        map[i]  = new int[width];
        temp[i] = new int[width];
        for (int j = 0; j < width; j++) {
            int x      = RandomInt(10);
            map[i][j]  = x < 7 ? 0 : 1;
            temp[i][j] = 0;
        }
    }
}

Life::~Life() {
}

int Life::Role23(int i, int j) {
    int c = map[i][j];
    int s = 0;
    for (int x = -1; x < 2; x++) {
        for (int y = -1; y < 2; y++) {
            int m = i; // row
            int n = j; // col
            m += x;
            n += y;
            m = (m + height) % height;
            n = (n + width) % width;
            s += map[m][n];
        }
    }
    s -= c;
    if (s == 3) {
        return 1;
    } else if (s == 2) {
        return c;
    } else {
        return 0;
    }
}

void Life::UpdateFrame() {
    // role 1
    static int f = 0;
    f++;
    if (f < 8) {
        return;
    }
    f = 0;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            temp[i][j] = Role23(i, j);
        }
    }
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            map[i][j] = temp[i][j];
        }
    }
}
