#pragma once
#ifndef SIMPLE_MAP_VIEW_H_
#define SIMPLE_MAP_VIEW_H_

#include "SimpleMap.hh"
#include "SimpleMapConfig.hh"
#include "WindowBase.hh"

class SimpleMapWindow : public WindowBase {
   private:
    SimpleMap map;

   public:
    SimpleMapWindow();

    ~SimpleMapWindow();

    virtual void show();
};

#endif