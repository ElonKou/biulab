#pragma once
#ifndef MENU_H_
#define MENU_H_

#include "ModulesManager.hh"
#include "WidgetBase.hh"

class Menu : public WidgetBase {
  public:
    ModulesManager* manager;

    Menu();

    ~Menu();

    virtual void Show();

    void ShowMenuFile();
};

#endif