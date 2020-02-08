/*================================================================
*  Copyright (C)2019 All rights reserved.
*  FileName : DataManager.cc
*  Author   : elonkou
*  Email    : elonkou@ktime.cc
*  Date     : 2020年01月05日 星期日 17时44分16秒
================================================================*/

#include "DataManager.hh"
DataManager* data_manager = new DataManager();

DataManager::DataManager() {
}

DataManager::~DataManager() {
}

bool DataManager::HasDataBase(string class_name) {
    auto item = biulab.find(class_name);
    if (item != biulab.end()) {
        return true;
    } else {
        return false;
    }
}

void DataManager::CreateDataBase(string class_name, Base* data_ptr) {
    biulab.insert(std::pair<string, Base*>(class_name, data_ptr));
}

void DataManager::DeleteDataBase(string class_name) {
    Base* base = operator[](class_name);
    if (base) {
        delete base;
    }
}

Base* DataManager::operator[](string class_name) {
    auto item = biulab.find(class_name);
    if (item != biulab.end()) {
        return item->second;
    } else {
        return nullptr;
    }
}