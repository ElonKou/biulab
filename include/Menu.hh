#pragma once
#ifndef MENU_H_
#define MENU_H_

#include "BiuLab.hh"
#include "Widget.hh"

namespace BiuLab {
namespace Widget {

class Menu : public Widget {
   private:
   public:
    Menu();

    ~Menu();

    void show();

    void showMenuFile();
};

}  // namespace Widget

}  // namespace BiuLab

#endif