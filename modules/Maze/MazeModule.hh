#pragma once
#ifndef MAZE_MODULE_H_
#define MAZE_MODULE_H_

#include "DataManager.hh"
#include "DynamicClass.hh"
#include "MazeController.hh"
#include "MazeControllerWindow.hh"
#include "MazeMap.hh"
#include "MazeMapWindow.hh"
#include "MazePerson.hh"
#include "ModuleBase.hh"

typedef struct MazeModuleData {
    MazePerson*                 per;
    MazeController*             con;
    MazeControllerWindow*       con_window;
    MazeMap*                    map;
    MazeMapWindow*              map_window;
    unordered_map<string, bool> target;
} MazeModuleData;

class MazeModule : public ModuleBase {
  public:
    MazeModuleData* data;

    MazeModule();

    ~MazeModule();

    virtual void UpdateData();

    virtual void UpdateModule();
};

#endif