/*================================================================
*  Copyright (C)2019 All rights reserved.
*  FileName : SimpleMapModule.cc
*  Author   : elonkou
*  Email    : elonkou@ktime.cc
*  Date     : 2019年12月29日 星期日 16时55分05秒
================================================================*/

#include "SimpleMapModule.hh"

using namespace std;

DYN_DECLARE(SimpleMapModule);

SimpleMapModule::SimpleMapModule() {
    module_name = "SimpleMapModule";
    data        = new SimpleMapData();
}

SimpleMapModule::~SimpleMapModule() {}

void SimpleMapModule::UpdateModule() {
    // window.Show();
}
