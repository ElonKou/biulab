#pragma once
#ifndef BIU_TYPES_H_
#define BIU_TYPES_H_

typedef union vec_2i {
    struct {
        int x;
        int y;
    };
    int v[2];
    vec_2i();
    vec_2i(int a, int b);
    vec_2i operator+(vec_2i other);
    void print();
} vec_2i;

#endif