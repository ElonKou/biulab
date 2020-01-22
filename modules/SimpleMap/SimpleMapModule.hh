#pragma once
#ifndef SIMPLE_MAP_MODULE_H_
#define SIMPLE_MAP_MODULE_H_

#include "ModuleBase.hh"
#include "PluginHelper.hh"
#include "SimpleMapWindow.hh"
#include "WindowBase.hh"

class SimpleMapModule : ModuleBase {
  private:
    SimpleMapWindow window;

  public:
    SimpleMapModule();

    ~SimpleMapModule();

    virtual void UpdateModule();
};

#endif