/*================================================================
*  Copyright (C)2019 All rights reserved.
*  FileName : DataManager.cc
*  Author   : elonkou
*  Email    : elonkou@ktime.cc
*  Date     : 2020年01月05日 星期日 17时44分16秒
================================================================*/

#include "DataManager.hh"

DataManager::DataManager() {
}

DataManager::~DataManager() {
}

DataBase* DataManager::Find(string class_name) {
    auto item = biulab_data.find(class_name);
    if (item != biulab_data.end()) {
        return item->second;
    } else {
        return nullptr;
    }
}

void DataManager::CreateDataBase(string class_name, DataBase* data_ptr) {
    biulab_data.insert(std::pair<string, DataBase*>(class_name, data_ptr));
}

void DataManager::DeleteDataBase(string class_name) {
    DataBase* base = Find(class_name);
    if (base) {
        delete (base);
    }
}