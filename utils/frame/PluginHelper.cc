/*================================================================
*  Copyright (C)2019 All rights reserved.
*  FileName : pluginhelper.cpp
*  Author   : elonkou
*  Email    : elonkou@ktime.cc
*  Date     : 2019年11月05日 星期二 21时11分38秒
================================================================*/

#include "PluginHelper.hh"

CPluginHelper::CPluginHelper() {}

CPluginHelper::~CPluginHelper() {}

std::vector<std::string> CPluginHelper::GetFileNameByPattern(
    std::string dir, const std::string& pattern) {
    std::vector<std::string> file_name_set;

    if (dir.empty()) {
        dir = "./";
    } else if (dir[dir.length() - 1] != '/') {
        dir += '/';
    }

    std::string strCmd = "ls " + dir + pattern;

    FILE* fp = popen(strCmd.c_str(), "r");

    if (!fp) {
        std::cerr << "fail to gain file-list" << std::endl;
        return file_name_set;
    }

    char buf[BUF_SIZE];
    while (fgets(buf, BUF_SIZE, fp)) {
        char* ws = strpbrk(buf, " \t\n");

        if (ws) {
            *ws = '\0';
        }

        file_name_set.push_back(std::string(buf));
    }

    pclose(fp);

    return file_name_set;
}

void CPluginHelper::Load(const std::string& dir, const std::string& pattern) {
    std::vector<std::string> soNameList = GetFileNameByPattern(dir, pattern);

    size_t i;
    for (i = 0; i < soNameList.size(); i++) {
        std::map<std::string, void*>::iterator itrSoName = m_SoNameTable.find(soNameList[i]);

        /* so-library has already loaded */
        if (itrSoName != m_SoNameTable.end()) {
            continue;
        }

        void* handle = dlopen(soNameList[i].c_str(), RTLD_LAZY);

        /* the very so-library file not exist */
        if (!handle) {
            std::cerr << dlerror() << std::endl;
            continue;
        }

        /* insert to SoNameTable */
        m_SoNameTable[soNameList[i]] = handle;
    }

    return;
}

void CPluginHelper::Unload(const std::string& dir, const std::string& pattern) {
    std::vector<std::string> soNameList = GetFileNameByPattern(dir, pattern);

    size_t i;
    for (i = 0; i < soNameList.size(); i++) {
        std::map<std::string, void*>::iterator itrSoName = m_SoNameTable.find(soNameList[i]);

        if (itrSoName != m_SoNameTable.end()) {
            void* handle = itrSoName->second;

            /* remove SoName */
            m_SoNameTable.erase(itrSoName);

            /* close so-library */
            dlclose(handle);
        }
    }

    m_ClassNameTable.clear();
    return;
}

void* CPluginHelper::Create(const std::string& className) {
    std::map<std::string, void*>::iterator itrClassName = m_ClassNameTable.find(className);

    CreateOBJ_T* create = 0;
    void*        pObj   = 0;

    /* class name found in ClassNameTable */
    if (itrClassName != m_ClassNameTable.end()) {
        if (0 != itrClassName->second) {
            create = (CreateOBJ_T*)dlsym(itrClassName->second, "createByClassName");

            if (create) {
                pObj = create(className.c_str());
            }
        }
    }
    /* class name not found in ClassNameTable */
    else {
        std::map<std::string, void*>::iterator itrSoName = m_SoNameTable.begin();

        /* traverse through SoNameTable */
        for (; itrSoName != m_SoNameTable.end(); ++itrSoName) {
            create = (CreateOBJ_T*)dlsym(itrSoName->second, "createByClassName");

            if (create) {
                pObj = create(className.c_str());

                if (pObj) {
                    m_ClassNameTable[className] = itrSoName->second;
                    break;
                }
            }
        }
    }

    return pObj;
}
