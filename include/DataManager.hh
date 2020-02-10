#pragma once
#ifndef DATA_MANAGER_H_
#define DATA_MANAGER_H_

#include "Base.hh"
#include "CoreBase.hh"
#include "DataBase.hh"
#include "ModuleBase.hh"
#include "WidgetBase.hh"
#include <sstream>
#include <unordered_map>

using namespace std;

typedef struct DataManagerInfoElem {
    bool  created;  // whether the data create by this module;
    Base* datatptr; // data pointer.
} DataManagerInfoElem;

class DataManager {
  private:
    unordered_map<string, unordered_map<string, DataManagerInfoElem>> biulab_data;

  public:
    unordered_map<string, Base*> biulab;

    DataManager();

    ~DataManager();

    bool HasDataBase(string class_name);

    void CreateDataBase(string module_name, string class_name, Base* data_ptr);

    void DeleteDataBase(string module_name, string class_name);

    void Display();

    Base* operator[](string class_name);
};

extern DataManager* data_manager;
template <typename T>
T* GetData(string class_name, string self_name) {
    return (T*)(*data_manager)[class_name];
}
#endif