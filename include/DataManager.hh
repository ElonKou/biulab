#pragma once
#ifndef DATA_MANAGER_H_
#define DATA_MANAGER_H_

#include "Base.hh"
#include "CoreBase.hh"
#include "DataBase.hh"
#include "ModuleBase.hh"
#include "WidgetBase.hh"
#include <unordered_map>

using namespace std;

class DataManager {
  public:
    unordered_map<string, Base*> biulab;

    DataManager();

    ~DataManager();

    bool HasDataBase(string class_name);

    void CreateDataBase(string class_name, Base* data_ptr);

    void DeleteDataBase(string class_name);

    Base* operator[](string class_name);
};

extern DataManager* data_manager;
template <typename T>
T* GetData(string class_name) {
    return (T*)(*data_manager)[class_name];
}
#endif