/*================================================================
*  Copyright (C)2019 All rights reserved.
*  FileName : Vec.cc
*  Author   : elonkou
*  Email    : elonkou@ktime.cc
*  Date     : 2019年10月02日 星期三 12时06分24秒
================================================================*/

#include "Vec.hh"
#include <iostream>
using namespace std;

vec_2i::vec_2i() {
    x = 0;
    y = 0;
}
vec_2i::vec_2i(int a, int b) : x(a), y(b) {}
vec_2i vec_2i::operator+(vec_2i other) {
    vec_2i v;
    v.x = x + other.x;
    v.y = y + other.y;
    return v;
}
void vec_2i::print() { cout << "(" << x << "," << y << ")"; }
