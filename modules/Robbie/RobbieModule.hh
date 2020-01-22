#pragma once
#ifndef ROBBIE_MODULE_H_
#define ROBBIE_MODULE_H_

#include "RobbieController.hh"
#include "RobbieMap.hh"

class RobbieModule {
  public:
    RobbieController con;

    RobbieMap map;

    RobbieModule();

    ~RobbieModule();
};

#endif