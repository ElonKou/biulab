#pragma once
#ifndef MODULES_MANAGER_H_
#define MODULES_MANAGER_H_

#include "MapModule.hh"
#include "RobbieModule.hh"

class ModulesManager {
   private:
   public:
    MapModule mapModule;
    RobbieModule robbieModule;
    ModulesManager();
    ~ModulesManager();
};

#endif