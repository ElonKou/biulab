#pragma once
#ifndef PROGRAMM_WINDOW_HH_
#define PROGRAMM_WINDOW_HH_

#include "BiuLabConfig.hh"
#include "ModuleBase.hh"
#include "WindowBase.hh"
#include "fstream"

class ModuleWindow : public WindowBase {
  public:
    ModuleWindow();

    ModuleWindow(ModulesManager* man);

    ~ModuleWindow();

    virtual void Show();
};

#endif
