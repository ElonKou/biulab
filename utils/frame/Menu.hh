#pragma once
#ifndef MENU_HH_
#define MENU_HH_

#include "ModulesManager.hh"
#include "WindowBase.hh"

class Menu : public WindowBase {
  public:
    ModulesManager* manager;

    Menu();

    ~Menu();

    virtual void Show();

    void ShowMenuFile();
};

#endif