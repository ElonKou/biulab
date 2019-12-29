/*================================================================
*  Copyright (C)2019 All rights reserved.
*  FileName : MapView.cc
*  Author   : elonkou
*  Email    : elonkou@ktime.cc
*  Date     : 2019年10月05日 星期六 16时07分35秒
================================================================*/

#include "MapView.hh"
#include <iostream>
#include "DynamicClass.hh"

using namespace std;

DYN_DECLARE(MapView);

MapView::MapView() {}

MapView::~MapView() {}

void MapView::show() {
    std::cout << "MapView is running..." << std::endl;
    std::cout << "MapView is running..." << std::endl;
}