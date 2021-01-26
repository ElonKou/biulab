#pragma once
#ifndef ROBBIE_WINDOW_HH_
#define ROBBIE_WINDOW_HH_

#include "RobbieController.hh"
#include "WindowBase.hh"

class RobbieControlWindow : public WindowBase {
  public:
    RobbieController* robbie_controll;

    RobbieControlWindow();

    RobbieControlWindow(ModulesManager* man);

    ~RobbieControlWindow();

    virtual void Show();
};

#endif