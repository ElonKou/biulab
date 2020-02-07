#pragma once
#ifndef MODULES_BASE_H_
#define MODULES_BASE_H_

#include "Base.hh"
#include <iostream>

class ModuleBase : public Base {
  public:
    ModuleBase() {}

    ~ModuleBase() {}

    void Init();

    virtual void UpdateModule() = 0;
};

#endif