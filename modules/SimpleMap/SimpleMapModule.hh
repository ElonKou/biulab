#pragma once
#ifndef SIMPLE_MAP_MODULE_H_
#define SIMPLE_MAP_MODULE_H_

#include "DataManager.hh"
#include "DynamicClass.hh"
#include "InspectWindow.hh"
#include "ModuleBase.hh"
#include "OverviewWindow.hh"
#include "PluginHelper.hh"
#include "SimpleMapWindow.hh"
#include "WindowBase.hh"

typedef struct SimpleMapData {
    SimpleMapWindow* map_window;
    InspectWindow*   insp_window;
    OverviewWindow*  over_window;
    SimpleMap*       simple_map;
    InspectInfo*     inspect_info;
    OverviewInfo*    overview_info;
} SimpleMapData;

class SimpleMapModule : ModuleBase {
  public:
    SimpleMapData* data;

    SimpleMapModule();

    ~SimpleMapModule();

    virtual void UpdateModule();

    void Check();
};

#endif