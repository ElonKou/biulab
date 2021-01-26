#pragma once
#ifndef ROBBIE_MODULE_HH_
#define ROBBIE_MODULE_HH_

#include "DynamicClass.hh"
#include "ModuleBase.hh"
#include "RobbieControlWindow.hh"
#include "RobbieController.hh"
#include "SimpleMap.hh"

typedef struct RobbieModuleData : public CoreBase {
    vector<SimpleMap*>   maps;
    SimpleMap*           dis_map;
    RobbieController*    controller;
    RobbieControlWindow* robbie_controll_window;
    unordered_map<string, bool> target;
    RobbieModuleData() {}
    ~RobbieModuleData() {}
} RobbieModuleData;

class RobbieModule : public ModuleBase {
  public:
    RobbieModuleData* data;

    RobbieModule();

    ~RobbieModule();

    virtual void UpdateModule();
};

#endif