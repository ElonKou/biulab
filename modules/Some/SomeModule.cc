/*================================================================
*  Copyright (C)2020 All rights reserved.
*  FileName : SomeModule.cc
*  Author   : elonkou
*  Email    : elonkou@ktime.cc
*  Date     : Wed 30 Dec 2020 07:23:29 PM CST
================================================================*/

#include "SomeModule.hh"

DYN_DECLARE(SomeModule);

SomeModule::SomeModule() {
}

SomeModule::~SomeModule() {
}

void SomeModule::UpdateModule() {
    std::cout << "Some Module is running..." << std::endl;
}
