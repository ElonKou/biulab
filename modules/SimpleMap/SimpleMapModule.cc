/*================================================================
*  Copyright (C)2019 All rights reserved.
*  FileName : SimpleMapModule.cc
*  Author   : elonkou
*  Email    : elonkou@ktime.cc
*  Date     : 2019年12月29日 星期日 16时55分05秒
================================================================*/

#include "SimpleMapModule.hh"
#include "DynamicClass.hh"
#include <iostream>

using namespace std;

DYN_DECLARE(SimpleMapModule);

SimpleMapModule::SimpleMapModule() {}

SimpleMapModule::~SimpleMapModule() {}

void SimpleMapModule::UpdateModule() {
    window.show();
}
