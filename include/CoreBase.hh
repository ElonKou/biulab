#pragma once
#ifndef COREBASE_HH_
#define COREBASE_HH_

#include "Base.hh"
#include "ModulesManager.hh"

class CoreBase : public Base {
  public:
    ModulesManager* manager;

    CoreBase() {}

    ~CoreBase() {}
};

#endif