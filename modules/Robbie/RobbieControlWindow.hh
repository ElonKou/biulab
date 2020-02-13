#pragma once
#ifndef ROBBIE_WINDOW_H_
#define ROBBIE_WINDOW_H_

#include "DataManager.hh"
#include "RobbieController.hh"
#include "WindowBase.hh"

class RobbieControlWindow : public WindowBase {
  private:
    RobbieController* robbie_controll;

  public:
    RobbieControlWindow() {}

    ~RobbieControlWindow() {}

    virtual void Show();

    virtual void UpdateData();
};

#endif