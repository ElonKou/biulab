#pragma once
#ifndef ROBBIE_MODULE_H_
#define ROBBIE_MODULE_H_

#include "DataManager.hh"
#include "DynamicClass.hh"
#include "ModuleBase.hh"
#include "ModulesManager.hh"
#include "RobbieControlWindow.hh"
#include "RobbieController.hh"
#include "SimpleMap.hh"

typedef struct RobbieModuleData : public DataBase {
    vector<SimpleMap*>          maps;
    SimpleMap*                  dis_map;
    RobbieController*           controller;
    RobbieControlWindow*        robbie_controll_window;
    unordered_map<string, bool> target;
    RobbieModuleData() {}
    ~RobbieModuleData() {}
    void UpdateData() {}
} RobbieModuleData;

class RobbieModule : public ModuleBase {
  public:
    RobbieModuleData* data;

    RobbieModule();

    ~RobbieModule();

    virtual void UpdateModule();

    virtual void UpdateData();
};

#endif