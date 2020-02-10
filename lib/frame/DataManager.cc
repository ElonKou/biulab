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

void DataManager::CreateDataBase(string module_name, string class_name, Base* data_ptr) {
    biulab.insert({class_name, data_ptr});
    // for (auto iter = biulab_data.begin(); iter != biulab_data.end(); iter++) {
    auto found_module = biulab_data.find(module_name);
    if (found_module != biulab_data.end()) {
        auto found = found_module->second.find(class_name);
        if (found == found_module->second.end()) {
            DataManagerInfoElem elem;
            elem.created  = true;
            elem.datatptr = data_ptr;
            found_module->second.insert({class_name, elem});
        }
    } else {
        DataManagerInfoElem elem;
        elem.created                                    = true;
        elem.datatptr                                   = data_ptr;
        unordered_map<string, DataManagerInfoElem> temp = {{class_name, elem}};
        biulab_data.insert({module_name, temp});
    }
}
void DataManager::DeleteDataBase(string module_name, string class_name) {
    Base* base = operator[](class_name);
    if (base) {
        delete base;
    }
}

void DataManager::Display() {
    for (auto it = biulab_data.begin(); it != biulab_data.end(); it++) {
        PrintSucceed(it->first + ":\n");
        for (auto iter = it->second.begin(); iter != it->second.end(); iter++) {
            string       ss;
            string       sss;
            stringstream xx;
            PrintSucceed("  " + iter->first + ":\n");
            ss = "    created: ";
            ss += iter->second.created ? "true\n" : "false\n";
            PrintSucceed(ss);
            xx << iter->second.datatptr;
            xx >> sss;
            sss = "    hasdata: " + sss + "\n";
            PrintSucceed(sss);
        }
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