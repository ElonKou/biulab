#pragma once
#ifndef SOME_HH_
#define SOME_HH_

#include "DynamicClass.hh"
#include "ModuleBase.hh"

class SomeModule : public ModuleBase {
  public:
    SomeModule();

    ~SomeModule();

    virtual void InitModule();

    virtual void UpdateModule();
};

#endif