#pragma once
#ifndef MENU_H_
#define MENU_H_

#include "WidgetBase.hh"

class Menu : public WidgetBase {
   private:
   public:
    Menu();

    ~Menu();

    virtual void show();

    void showMenuFile();
};

#endif