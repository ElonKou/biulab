#pragma once
#ifndef MAP_VIEW_H_
#define MAP_VIEW_H_

#include "WindowBase.hh"

class MapView : public WindowBase {
   public:
    MapView();

    ~MapView();

    virtual void show();
};

#endif