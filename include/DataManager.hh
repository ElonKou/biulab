#pragma once
#ifndef DATA_MANAGER_H_
#define DATA_MANAGER_H_

#include "DataBase.hh"
#include <unordered_map>

using namespace std;

class DataManager {
  public:
    unordered_map<string, DataBase*> biulab_data;

    DataManager();

    ~DataManager();

    DataBase* Find(string class_name);

    void CreateDataBase(string class_name, DataBase* data_ptr);

    void DeleteDataBase(string class_name);
};

#endif