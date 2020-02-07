#pragma once
#ifndef SIMPLE_MAP_WINDOW_H_
#define SIMPLE_MAP_WINDOW_H_

#include "DataManager.hh"
#include "MapEditor.hh"
#include "SimpleMap.hh"
#include "SimpleMapConfig.hh"
#include "WindowBase.hh"

class SimpleMapWindow : public WindowBase {
  private:
    bool       has_map;
    SimpleMap* simple_map;
    MapEditor* map_editor;

  public:
    SimpleMapWindow();

    ~SimpleMapWindow();

    virtual void Show();

    void UpdateData();
};

#endif