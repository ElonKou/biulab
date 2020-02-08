#pragma once
#ifndef MAP_EDITOR_MODULE_H_
#define MAP_EDITOR_MODULE_H_

#include "DataManager.hh"
#include "DynamicClass.hh"
#include "InspectWindow.hh"
#include "MapEditor.hh"
#include "MapEditorWindow.hh"
#include "ModuleBase.hh"
#include "OverviewWindow.hh"
#include "SimpleMapWindow.hh"

typedef struct MapEditorData {
    MapEditorWindow* map_editor_window;
    SimpleMapWindow* simple_map_window;
    OverviewWindow*  overview_window;
    InspectWindow*   insepect_window;
    InspectInfo*     inspect_info;
    OverviewInfo*    overview_info;
    MapEditor*       map_editor;
    SimpleMap*       simple_map;
} MapEditorData;

class MapEditorModule : public ModuleBase {
  private:
  public:
    MapEditorData* data;

    MapEditorModule();

    ~MapEditorModule();

    virtual void UpdateModule();

    void Check();
};

#endif