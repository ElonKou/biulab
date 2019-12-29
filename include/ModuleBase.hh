#pragma once
#ifndef MODULES_BASE_H_
#define MODULES_BASE_H_

#include "BiuLabConfig.hh"

class ModuleBase {
   public:
    ModuleBase() {}

    ~ModuleBase() {}

    virtual void UpdateModule() = 0;
};

#endif