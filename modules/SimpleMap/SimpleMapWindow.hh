#pragma once
#ifndef SIMPLE_MAP_WINDOW_H_
#define SIMPLE_MAP_WINDOW_H_

#include "DataManager.hh"
#include "Lib.hh"
#include "MapEditorBase.hh"
#include "SimpleMap.hh"
#include "SimpleMapConfig.hh"
#include "WindowBase.hh"

class SimpleMapWindow : public WindowBase {
  public:
    float          bsize;
    float          padding;
    SimpleMap*     simple_map;
    MapEditorBase* map_editor;

    SimpleMapWindow();

    ~SimpleMapWindow();

    virtual void Show();

    void UpdateData();
};

#endif