#include "MazePerson.hh"

using namespace std;

MazePerson::MazePerson()
    : step_count(0)
    , algorithm_name("RightFirst")
    , cur_pos({2, 6})
    , forward(DIR_UP) {
}

MazePerson::~MazePerson() {
}

void MazePerson::TurnLeft() {
    forward = ForwardDirection((forward + 3) % 4);
}

void MazePerson::TurnRight() {
    forward = ForwardDirection((forward + 1) % 4);
}

void MazePerson::GoAhead() {
    switch (forward) {
    case DIR_UP:
        cur_pos = cur_pos + vec_2i(0, -1);
        break;
    case DIR_DOWN:
        cur_pos = cur_pos + vec_2i(0, 1);
        break;
    case DIR_LEFT:
        cur_pos = cur_pos + vec_2i(-1, 0);
        break;
    case DIR_RIGHT:
        cur_pos = cur_pos + vec_2i(1, 0);
        break;
    default:
        break;
    }
    step_count++;
}

void MazePerson::Start() {
    while (!map->CheckExit(cur_pos)) {
        NextStep();
    }
}

void MazePerson::NextStep() {
    if (!(map->CheckExit(cur_pos))) {
        vec_2i this_forward = vec_2i(0, 0);
        vec_2i this_right   = vec_2i(0, 0);
        vec_2i this_left    = vec_2i(0, 0);
        switch (forward) {
        case DIR_UP:
            this_forward = cur_pos + vec_2i(0, -1);
            this_right   = cur_pos + vec_2i(1, 0);
            this_left    = cur_pos + vec_2i(-1, 0);
            break;
        case DIR_DOWN:
            this_forward = cur_pos + vec_2i(0, 1);
            this_right   = cur_pos + vec_2i(-1, 0);
            this_left    = cur_pos + vec_2i(1, 0);
            break;
        case DIR_LEFT:
            this_forward = cur_pos + vec_2i(-1, 0);
            this_right   = cur_pos + vec_2i(0, -1);
            this_left    = cur_pos + vec_2i(0, 1);
            break;
        case DIR_RIGHT:
            this_forward = cur_pos + vec_2i(1, 0);
            this_right   = cur_pos + vec_2i(0, 1);
            this_left    = cur_pos + vec_2i(0, -1);
            break;
        default:
            break;
        }
        if (algorithm_name == "RightFirst") {
            if (map->CheckWallOrNot(this_right)) {
                if (map->CheckWallOrNot(this_forward)) {
                    TurnLeft();
                } else {
                    GoAhead();
                }
            } else {
                TurnRight();
                GoAhead();
            }
        } else {
            if (map->CheckWallOrNot(this_left)) {
                if (map->CheckWallOrNot(this_forward)) {
                    TurnRight();
                } else {
                    GoAhead();
                }
            } else {
                TurnLeft();
                GoAhead();
            }
        }
    }
}