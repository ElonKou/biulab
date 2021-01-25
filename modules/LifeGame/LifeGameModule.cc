/*================================================================
*  Copyright (C)2020 All rights reserved.
*  FileName : LifeGameModule.cc
*  Author   : elonkou
*  Email    : elonkou@ktime.cc
*  Date     : 2020年02月23日 星期日 17时57分35秒
================================================================*/

#include "LifeGameModule.hh"

DYN_DECLARE(LifeGameModule);

LifeGameModule::LifeGameModule() {
    module_name = "LifeGameModule";
    data             = new LifeGameModuleData();
    data->map_base   = new LifeGameMapOne();
    data->rule_base  = new LifeGameRuleOne();
    data->con        = new LifeGameController();
    data->con_window = new LifeGameControllerWindow();

    data->con->map_base   = data->map_base;
    data->con->rule_base  = data->rule_base;
    data->con_window->con = data->con;
}

LifeGameModule::~LifeGameModule() {
}

void LifeGameModule::UpdateModule() {
    if (data->map_base && data->con_window->manager->options.show_map_window) {
        data->map_base->Show();
    }
    if (data->con_window && data->con_window->manager->options.show_control_window) {
        data->con_window->Show();
    }
}