#pragma once
#ifndef COREBASE_HH_
#define COREBASE_HH_

#include "Base.hh"
#include "ModuleBase.hh"

class CoreBase : public Base {
  public:
    ModulesManager* manager;

    CoreBase() {}

    ~CoreBase() {}
};

#endif