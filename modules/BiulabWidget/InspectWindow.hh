#pragma once
#ifndef INSPECT_WINDOW_H_
#define INSPECT_WINDOW_H_

#include "Lib.hh"
#include "WindowBase.hh"
#include <unordered_map>
#include <vector>

typedef struct InspectItem {
    int            index;
    bool           collapsed;
    string         selected;
    string         title;
    vector<string> data;
} InspectItem;

typedef struct InspectList {
    vector<InspectItem> items;
} InspectList;

class InspectWindow : public WindowBase {
  private:
    InspectList item_list;

  public:
    InspectWindow();

    ~InspectWindow();

    virtual void Show();

    void UpdateInspectItemList(InspectList list);
};

#endif