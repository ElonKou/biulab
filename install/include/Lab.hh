#pragma once
#ifndef LAB_H_
#define LBB_H_

#include "MainWindow.hh"
#include "ModulesManager.hh"

class Lab {
   private:
    string root;
    int version;

   public:
    MainWindow window;

    ModulesManager manager;

    Lab();

    ~Lab();

    void initLab();

    void start();
};

#endif