#pragma once
#ifndef PROGRAMM_WINDOW_HH_
#define PROGRAMM_WINDOW_HH_

#include "BiuLab.hh"
#include "BiuLabConfig.hh"
#include "ModulesManager.hh"
#include "WindowBase.hh"
#include "fstream"

class ModuleWindow : public WindowBase {
  public:
    ModulesManager* manager;

    ModuleWindow();

    ~ModuleWindow();

    virtual void Show();
};

#endif
