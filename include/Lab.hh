#pragma once
#ifndef LAB_HH_
#define LBB_HH_

#include "MainViewport.hh"
#include "ModulesManager.hh"

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

    void Start();
};

#endif