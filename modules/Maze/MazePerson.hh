#pragma
#ifndef _MAZE_PERSON_H_
#define _MAZE_PERSON_H_

#include "BiuLabTypes.hh"
#include "MazeMap.hh"
#include "MazePerson.hh"
#include <iostream>

typedef enum {
    DIR_UP,
    DIR_RIGHT,
    DIR_DOWN,
    DIR_LEFT
} ForwardDirection;

class MazePerson : public CoreBase {
  public:
    int              step_count;
    string           algorithm_name;
    vec_2i           cur_pos;
    ForwardDirection forward;
    ForwardDirection start_forward;
    MazeMap*         maze_map;

    MazePerson();
    ~MazePerson();
    void GoAhead();
    void TurnLeft();
    void TurnRight();
    void Start();
    void NextStep();
};

#endif