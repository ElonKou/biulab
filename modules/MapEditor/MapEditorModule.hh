#pragma once
#ifndef MAP_MODULE_H_
#define MAP_MODULE_H_

#include "InspectWindow.hh"
#include "MapEditorWindow.hh"
#include "ModuleBase.hh"
#include "OverviewWindow.hh"
#include "SimpleMapWindow.hh"

class MapEditorModule : public ModuleBase {
   private:
    MapEditorWindow map_editor_window;

    SimpleMapWindow simple_map_window;

    InspectWindow insepect_window;

    OverviewWindow overview_window;

   public:
    MapEditorModule();

    ~MapEditorModule();

    virtual void UpdateModule();
};

#endif