/*================================================================
*  Copyright (C)2020 All rights reserved.
*  FileName : LifeGameRuleOne.cc
*  Author   : elonkou
*  Email    : elonkou@ktime.cc
*  Date     : 2020年03月07日 星期六 00时47分13秒
================================================================*/

#include "LifeGameRuleOne.hh"

LifeGameRuleOne::LifeGameRuleOne() {
    size = pow(ELEM_ONE_SIZE, ELEM_ONE_RANGE);
}

LifeGameRuleOne::~LifeGameRuleOne() {
}

LifeGameElem LifeGameRuleOne::GetAction(int rule_id, vector<LifeGameElem> values) {
    vector<LifeGameElem> rules = GetRule(rule_id);
    size_t               index = 0;
    for (size_t i = 0; i < values.size(); ++i) {
        index += (2 << i) * int(values[values.size() - 1 - i]);
    }
    return rules[index];
}

vector<LifeGameElem> LifeGameRuleOne::GetRule(int rule_id) {
    vector<LifeGameElem> rules(size);
    for (size_t i = 0; i < size; i++) {
        if (rule_id & (1 << i)) {
            rules[size - 1 - i] = ElemAlive;
        }
    }
    return rules;
}
