#pragma once
#ifndef INSPECT_WINDOW_H_
#define INSPECT_WINDOW_H_

#include "DataManager.hh"
#include "Lib.hh"
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
} InspectInfo;

class InspectWindow : public WindowBase {
  private:
    InspectInfo* info;

  public:
    InspectWindow();

    ~InspectWindow();

    virtual void Show();

    void UpdateData();
};

#endif