#pragma once
#ifndef WIDGHT_H_

#include <string>
#include "BiuLab.hh"

using namespace std;

namespace BiuLab {
namespace Widget {

class Widget {
   private:
   public:
    Widget();

    ~Widget();

    void showHelpMarker(const string dsec);
};

}  // namespace Widget
}  // namespace BiuLab

#define WIDGHT_H_
#endif