#pragma once
#ifndef INSPECT_WINDOW_H_
#define INSPECT_WINDOW_H_

#include "DataManager.hh"
#include "Lib.hh"
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

typedef struct InspectInfo : public DataBase {
    unordered_map<string, InspectItem> items;
    MapBase*                           simple_map;
    OverviewInfo*                      overview_info;
    WindowBase*                        map_editor_window;
    void                               AddInfo(string path, string pattern, bool target);
    void                               UpdateFunc(string maps_path);
    void                               UpdateData();
} InspectInfo;

class InspectWindow : public WindowBase {
  public:
    InspectInfo* info;

    InspectWindow();

    ~InspectWindow();

    virtual void Show();

    void UpdateData();
};

#endif