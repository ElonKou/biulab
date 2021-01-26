#pragma once
#ifndef LAB_HH_
#define LBB_HH_

#include "MainViewport.hh"
#include "ModuleBase.hh"

class Lab {
  private:
    string root;
    int    version;

  public:
    ModulesManager* manager;

    MainViewport* viewport;

    Lab();

    ~Lab();

    void InitLab();

    void Run();
};

#endif