#pragma once
#ifndef MENU_HH_
#define MENU_HH_

#include "ModulesManager.hh"
#include "WindowBase.hh"

class Menu : public WindowBase {
  public:
    Menu();

    Menu(ModulesManager* man);

    ~Menu();

    virtual void Show();

    void ShowMenuFile();
};

#endif