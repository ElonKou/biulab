#pragma once
#ifndef MODULES_BASE_HH_
#define MODULES_BASE_HH_

#include "Base.hh"
#include <iostream>

class ModuleBase : public Base {
  public:
    string module_name;

    ModuleBase() {}

    ~ModuleBase() {}

    void Init();

    virtual void UpdateModule() = 0;
};

#endif