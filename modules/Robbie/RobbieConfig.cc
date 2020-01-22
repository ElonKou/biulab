/*================================================================
*  Copyright (C)2019 All rights reserved.
*  FileName : RobbieConfig.cc
*  Author   : elonkou
*  Email    : elonkou@ktime.cc
*  Date     : 2019年10月02日 星期三 16时21分33秒
================================================================*/

#include "RobbieConfig.hh"

Strategy::Strategy() {}
Strategy::Strategy(int k, int w, int h)
    : key(k)
    , wmove(w)
    , hmove(h) {}
Strategy::~Strategy() {}