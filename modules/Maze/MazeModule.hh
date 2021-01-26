#pragma once
#ifndef MAZE_MODULE_HH_
#define MAZE_MODULE_HH_

#include "DynamicClass.hh"
#include "MazeController.hh"
#include "MazeControllerWindow.hh"
#include "MazeMap.hh"
#include "MazeMapWindow.hh"
#include "MazePerson.hh"
#include "ModuleBase.hh"

typedef struct MazeModuleData {
    MazePerson*           per;
    MazeController*       con;
    MazeControllerWindow* con_window;
    MazeMap*              map;
    MazeMapWindow*        map_window;
} MazeModuleData;

class MazeModule : public ModuleBase {
  public:
    MazeModuleData* data;

    MazeModule();

    ~MazeModule();

    virtual void InitModule();

    virtual void UpdateModule();
};

#endif