#pragma once
#ifndef SIMPLE_MAP_WINDOW_H_
#define SIMPLE_MAP_WINDOW_H_

#include "MapEditor.hh"
#include "SimpleMap.hh"
#include "SimpleMapConfig.hh"
#include "WindowBase.hh"

class SimpleMapWindow : public WindowBase {
  private:
    bool       has_map;
    SimpleMap* map;
    MapEditor* map_editor;

  public:
    SimpleMapWindow();

    ~SimpleMapWindow();

    virtual void show();

    void SetCores(MapEditor* map_editor_, SimpleMap* simple_map_);

    void ClearCores();
};

#endif