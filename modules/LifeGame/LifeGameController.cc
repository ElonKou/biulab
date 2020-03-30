/*================================================================
*  Copyright (C)2020 All rights reserved.
*  FileName : LifeGameController.cc
*  Author   : elonkou
*  Email    : elonkou@ktime.cc
*  Date     : 2020年02月23日 星期日 17时43分47秒
================================================================*/

#include "LifeGameController.hh"

void LifeGameController::UpdateSize(int width, int history) {
    map_base->UpdateSize(width, history);
}

void LifeGameController::UpdateRule(int rule_id) {
    map_base->UpdateMap(*rule_base, rule_id);
}

void LifeGameController::RandomElems(int rate) {
    map_base->RandomElems(rate);
}

LifeGameController::LifeGameController() {
}

LifeGameController::~LifeGameController() {
}
