#pragma once
#ifndef MAP_MODULE_H_
#define MAP_MODULE_H_

#include "MapEditor.hh"

class MapModule {
   public:
    MapEditor mapEditor;

    MapModule();

    ~MapModule();
};

#endif