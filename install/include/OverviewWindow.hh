#pragma once
#ifndef OVERVIEW_WINDOW_H_
#define OVERVIEW_WINDOW_H_

#include "WindowBase.hh"

class OverviewWindow : public WindowBase {
   public:
    OverviewWindow();

    ~OverviewWindow();

    virtual void show();
};

#endif