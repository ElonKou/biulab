#pragma once
#ifndef OVERVIEW_WINDOW_HH_
#define OVERVIEW_WINDOW_HH_

#include "WindowBase.hh"
#include <unordered_map>
#include <vector>

typedef struct OverviewInfo : public WindowBase {
    unordered_map<string, unordered_map<string, string>> items;
    void UpdateFunc();
} OverWindowInfo;

class OverviewWindow : public WindowBase {
  public:
    OverviewInfo* info;

    OverviewWindow();

    ~OverviewWindow();

    virtual void Show();
};

#endif