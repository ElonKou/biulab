#pragma once
#ifndef MAP_EDITOR_MODULE_H_
#define MAP_EDITOR_MODULE_H_

#include "InspectWindow.hh"
#include "MapEditorWindow.hh"
#include "ModuleBase.hh"
#include "OverviewWindow.hh"
#include "SimpleMapWindow.hh"

class MapEditorModule : public ModuleBase {
  private:
    MapEditorWindow map_editor_window;

    SimpleMapWindow simple_map_window;

    OverviewWindow overview_window;

    InspectWindow insepect_window;

    MapEditor* map_editor;

    SimpleMap* simple_map;

  public:
    MapEditorModule();

    ~MapEditorModule();

    virtual void UpdateModule();

    void Init();
};

#endif