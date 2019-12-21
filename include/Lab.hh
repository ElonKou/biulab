#pragma once
#ifndef LAB_H_
#define LBB_H_

#include "MainWindow.hh"
#include "ModulesManager.hh"

using namespace BiuLab::Window;
using namespace BiuLab::Modules;

namespace BiuLab {

class Lab {
   private:
   public:
    MainWindow window;

    ModulesManager manager;

    Lab();

    ~Lab();

    void start();
};

}  // namespace BiuLab

#endif