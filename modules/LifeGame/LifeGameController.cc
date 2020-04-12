/*================================================================
*  Copyright (C)2020 All rights reserved.
*  FileName : LifeGameController.cc
*  Author   : elonkou
*  Email    : elonkou@ktime.cc
*  Date     : 2020年02月23日 星期日 17时43分47秒
================================================================*/

#include "LifeGameController.hh"

void LifeGameController::UpdateSize(int width, int height) {
    map_base->UpdateSize(width, height);
}

void LifeGameController::UpdateRule(int rule_id) {
    map_base->UpdateMap(*rule_base, rule_id);
}

void LifeGameController::UpdateRuleMax(int rule_id, int max_height) {
    vec_2i size = map_base->GetSize();
    for (int i = size.y; i < max_height; i++) {
        UpdateRule(rule_id);
    }
}

void LifeGameController::RandomElems(int rate) {
    map_base->RandomElems(rate);
}

LifeGameController::LifeGameController() {
}

LifeGameController::~LifeGameController() {
}
