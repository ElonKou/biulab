/*================================================================
*  Copyright (C)2020 All rights reserved.
*  FileName : LifeModule.cc
*  Author   : elonkou
*  Email    : elonkou@ktime.cc
*  Date     : Mon 01 Feb 2021 05:02:48 PM CST
================================================================*/

#include "LifeModule.hh"

DYN_DECLARE(LifeModule);

LifeModule::LifeModule() {
}

LifeModule::~LifeModule() {
}

void LifeModule::InitModule() {
    life         = new Life();
    window       = new LifeWindow();
    con          = new LifeController();
    window->life = life;
    con->life    = life;
}

void LifeModule::UpdateModule() {
    if (window && window->life && manager->options.show_map_window) {
        window->Show();
    }
    if (con && con->life && manager->options.show_control_window) {
        con->Show();
    }
    if (life) {
        life->UpdateFrame();
    }
}