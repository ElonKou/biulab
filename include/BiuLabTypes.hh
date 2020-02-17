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
    vec_2i          operator+(const vec_2i other);
    friend ostream& operator<<(ostream& os, const vec_2i& v);
} vec_2i;

namespace std {
template <>
struct hash<vec_2i> {
    std::size_t operator()(vec_2i const& v) const noexcept {
        using std::hash;
        using std::size_t;
        using std::string;
        return ((hash<int>{}(v.x)) ^ (hash<int>{}(v.y) << 1));
    }
};
} // namespace std

bool operator==(const vec_2i& first, const vec_2i& second);

#endif