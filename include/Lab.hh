#pragma once
#ifndef LAB_H_
#define LBB_H_

#include "ModulesManager.hh"
#include "WindowView.hh"

namespace BiuLab {

class Lab {
   private:
   public:
    WindowView window;
    ModulesManager manager;
    Lab();
    ~Lab();
    void start();
};

}  // namespace BiuLab

#endif