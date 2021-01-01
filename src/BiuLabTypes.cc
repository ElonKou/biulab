/*================================================================
*  Copyright (C)2019 All rights reserved.
*  FileName : frame/BiuLabTypes.cc
*  Author   : elonkou
*  Email    : elonkou@ktime.cc
*  Date     : 2019年12月30日 星期一 21时44分24秒
================================================================*/

#include "BiuLabTypes.hh"

bool operator==(const vec_2i& first, const vec_2i& second) {
    return (first.x == second.x) && (first.y == second.y);
}

vec_2i::vec_2i() {
    x = 0;
    y = 0;
}

vec_2i::vec_2i(int a, int b)
    : x(a)
    , y(b) {}

vec_2i vec_2i::operator+(const vec_2i other) {
    vec_2i v;
    v.x = x + other.x;
    v.y = y + other.y;
    return v;
}

vec_2i vec_2i::operator-(const vec_2i other) {
    vec_2i v;
    v.x = x - other.x;
    v.y = y - other.y;
    return v;
}

ostream& operator<<(ostream& os, const vec_2i& v) {
    os << "(" << v.x << ", " << v.y << ")";
    return os;
}
