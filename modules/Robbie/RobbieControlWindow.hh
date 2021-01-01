#pragma once
#ifndef ROBBIE_WINDOW_HH_
#define ROBBIE_WINDOW_HH_

#include "RobbieController.hh"
#include "WindowBase.hh"

class RobbieControlWindow : public WindowBase {
  private:
    RobbieController* robbie_controll;

  public:
    RobbieControlWindow() {}

    ~RobbieControlWindow() {}

    virtual void Show();
};

#endif