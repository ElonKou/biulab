#pragma once
#ifndef OVERVIEW_WINDOW_H_
#define OVERVIEW_WINDOW_H_

#include "DataManager.hh"
#include "WindowBase.hh"
#include <unordered_map>
#include <vector>

typedef struct OverviewInfo : public DataBase {
    unordered_map<string, unordered_map<string, string>> items;
    void                                                 UpdateData();
    void                                                 UpdateFunc();
} OverWindowInfo;

class OverviewWindow : public WindowBase {
  public:
    OverviewInfo* info;

    OverviewWindow();

    ~OverviewWindow();

    virtual void Show();

    void UpdateData();
};

#endif