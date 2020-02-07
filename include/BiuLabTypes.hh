#pragma once
#ifndef BIU_TYPES_H_
#define BIU_TYPES_H_

#include <ostream>
using namespace std;

typedef union vec_2i {
    struct {
        int x;
        int y;
    };
    int v[2];
    vec_2i();
    vec_2i(int a, int b);
    vec_2i          operator+(vec_2i other);
    friend ostream& operator<<(ostream& os, const vec_2i& v);
} vec_2i;

#endif