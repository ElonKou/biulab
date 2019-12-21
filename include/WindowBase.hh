#pragma once
#ifndef WINDOW_BASE_H_

#include "BiuLab.hh"
#include "Widget.hh"

using namespace BiuLab::Widget;

namespace BiuLab {
namespace Widget {

class WindowBase : public Widget {
   private:
   public:
    WindowBase();
    virtual ~WindowBase();
    virtual void show() = 0;
};

}  // namespace Widget
}  // namespace BiuLab

#define WINDOW_BASE_H_
#endif