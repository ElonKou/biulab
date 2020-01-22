/*================================================================
*  Copyright (C)2019 All rights reserved.
*  FileName : lib/frame/BiuLabTypes.cc
*  Author   : elonkou
*  Email    : elonkou@ktime.cc
*  Date     : 2019年12月30日 星期一 21时44分24秒
================================================================*/

#include "BiuLabTypes.hh"
#include <iostream>

using namespace std;
vec_2i::vec_2i() {
    x = 0;
    y = 0;
}
vec_2i::vec_2i(int a, int b)
    : x(a)
    , y(b) {}
vec_2i vec_2i::operator+(vec_2i other) {
    vec_2i v;
    v.x = x + other.x;
    v.y = y + other.y;
    return v;
}
void vec_2i::print() { cout << "(" << x << "," << y << ")"; }
