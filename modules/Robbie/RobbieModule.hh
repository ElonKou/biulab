#pragma once
#ifndef ROBBIE_MODULE_HH_
#define ROBBIE_MODULE_HH_

#include "DynamicClass.hh"
#include "ModuleBase.hh"
#include "RobbieControlWindow.hh"
#include "RobbieController.hh"
#include "SimpleMap.hh"
#include "SimpleMapWindow.hh"

typedef struct RobbieModuleData {
    vector<SimpleMap*>   maps;
    SimpleMap*           dis_map;
    RobbieController*    controller;
    RobbieControlWindow* rc_window;
    SimpleMapWindow*     map_window;
} RobbieModuleData;

class RobbieModule : public ModuleBase {
  public:
    RobbieModuleData* data;

    RobbieModule();

    ~RobbieModule();

    virtual void InitModule();

    virtual void UpdateModule();
};

#endif