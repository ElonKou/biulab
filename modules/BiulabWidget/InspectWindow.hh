#pragma once
#ifndef INSPECT_WINDOW_H_
#define INSPECT_WINDOW_H_

#include <unordered_map>
#include <vector>
#include "WindowBase.hh"

typedef struct InspectItem {
    int index;
    string selected;
    string title;
    vector<string> data;
} InspectItem;

typedef struct InspectList {
    bool collapsed;
    vector<InspectItem> items;
} InspectList;

class InspectWindow : public WindowBase {
   private:
    InspectList item_list;

   public:
    InspectWindow();

    ~InspectWindow();

    virtual void show();
};

#endif