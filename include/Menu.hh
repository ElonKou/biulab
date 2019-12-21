#pragma once
#ifndef MENU_H_
#define MENU_H_

#include "BiuLab.hh"
#include "Widget.hh"

namespace BiuLab {
namespace Widget {

class Menu : public Widget {
   private:
    void showMenuFile();

   public:
    Menu();

    ~Menu();

    void show();
};

}  // namespace Widget

}  // namespace BiuLab

#endif