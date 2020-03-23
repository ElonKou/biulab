/*================================================================
*  Copyright (C)2020 All rights reserved.
*  FileName : LifeGameMapOne.cc
*  Author   : elonkou
*  Email    : elonkou@ktime.cc
*  Date     : 2020年03月07日 星期六 00时47分50秒
================================================================*/

#include "LifeGameMapOne.hh"

LifeGameMapOne::LifeGameMapOne() {
    size = LIFE_GAME_DIM_WIDTH;
    map  = new LifeGameElem[size];
    RandomElems();
    cout << "LifeGameMapOne" << endl;
}

LifeGameMapOne::LifeGameMapOne(size_t size_, bool ring_)
    : size(size_) {
    map = new LifeGameElem[size];
    RandomElems();
}

LifeGameMapOne::~LifeGameMapOne() {
}

void LifeGameMapOne::Show() {
    if (ImGui::Begin("LifeGameMapOne", &show_mapeditor_window, 0)) {
        if (ImGui::Button("dsada")) {
            cout << "dasda" << endl;
        }
    }
    ImGui::End();
}

void LifeGameMapOne::UpdateData() {}

void LifeGameMapOne::RandomElems(int rate) {
    for (size_t i = 0; i < size; i++) {
        int rand = RandomInt(100);
        if (rand <= rate) {
            map[i] = ElemAlive;
        } else {
            map[i] = ELemDead;
        }
    }
}

void LifeGameMapOne::UpdateMap(LifeGameRuleBase& rule) {
    LifeGameElem* temp = new LifeGameElem[size];
    for (size_t i = 0; i < size; i++) {
        vector<LifeGameElem> elems = {map[(i - 1 + size) % size], map[i], map[(i + 1) % size]};
        map[i]                     = rule.GetAction(12, elems);
    }
    for (size_t i = 0; i < size; i++) {
        map[i] = temp[i];
    }
    delete[] temp;
}