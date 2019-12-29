#pragma once
#ifndef MAP_VIEW_H_
#define MAP_VIEW_H_

#include "WindowBase.hh"

class MapEditorWindow : public WindowBase {
   public:
    MapEditorWindow();

    ~MapEditorWindow();

    virtual void show();
};

#endif