#pragma once
#ifndef INSPECT_WINDOW_HH_
#define INSPECT_WINDOW_HH_

#include "Lib.hh"
#include "MainViewport.hh"
#include "MapBase.hh"
#include "OverviewWindow.hh"
#include "WindowBase.hh"
#include <unordered_map>

typedef struct InspectInfoItem {
    bool           collapsed;
    bool           changed;
    string         selected;
    string         title;
    vector<string> data;
} InspectItem;

typedef struct InspectInfo : public CoreBase {
    unordered_map<string, InspectItem> items;
    MapBase*      simple_map;
    OverviewInfo* overview_info;
    WindowBase*   map_editor_window;
    void AddInfo(string path, string pattern, bool target);
    void UpdateFunc(string maps_path);
} InspectInfo;

class InspectWindow : public WindowBase {
  public:
    InspectInfo* info;

    InspectWindow();

    ~InspectWindow();

    virtual void Show();
};

#endif