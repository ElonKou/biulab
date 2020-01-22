#ifndef __PLUGINHELPER_H__
#define __PLUGINHELPER_H__

#include <dlfcn.h>
#include <iostream>
#include <map>
#include <stdio.h>
#include <string.h>
#include <string>
#include <vector>

#define BUF_SIZE 1024

typedef void* CreateOBJ_T(const char* strClassName);
typedef void  DeleteOBJ_T(void* p);

class CPluginHelper {
  public:
    CPluginHelper();
    ~CPluginHelper();

  public:
    /* load so-library file(s)
     *
     * @param dir:     path of so-library
     * @param pattern: name of so-library file(s), such as '*.so', 'aaa.so'
     *
     */
    void Load(const std::string& dir, const std::string& pattern);

    /* unload so-library file(s)
     *
     * @param dir:     path of so-library
     * @param pattern: name of so-library file(s), such as '*.so', 'aaa.so'
     *
     */
    void Unload(const std::string& dir, const std::string& pattern);

    /* create object from so-library file(s) by class name
     *
     * @param className:   class name
     *
     * @return:            void-type pointer which references to the new created
     * object
     *
     */
    void* Create(const std::string& className);

  private:
    /* get list of filename by pattern
     *
     * @param dir:     path of so-library
     * @param pattern: name of so-library file(s), such as '*.so', 'aaa.so'
     *
     * @return:        list of file name
     *
     */
    std::vector<std::string> GetFileNameByPattern(std::string        dir,
                                                  const std::string& pattern);

    /* a cache table mapping so-library file'name to its handle */
    std::map<std::string, void*> m_SoNameTable;

    /* a cache table mapping class-name to some so-library file handle */
    std::map<std::string, void*> m_ClassNameTable;
};

#endif /* __PLUGINHELPER_H__ */
