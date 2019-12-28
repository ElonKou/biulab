#ifndef __DYNAMIC_H__
#define __DYNAMIC_H__

#include <string.h>
#include <cstdio>
#include <string>
#include <typeinfo>

#if !defined(DYN_DECLARE)
#define DYN_DECLARE(class_name) DYN_CLASS::CFactory<class_name> class_name
#endif

#if !defined(DYN_CREATE)
#define DYN_CREATE(class_name) DYN_CLASS::Create(class_name)
#endif

namespace DYN_CLASS {
/* create object by class name */
void* Create(const char* class_name);

/* interface of class factory*/
class CAbstractFactory {
   public:
    virtual void* Create(const char* class_name) = 0;
};

/* list of class factory */
class CFactoryList {
    friend void* Create(const char* class_name);

    static CFactoryList* _head;
    CFactoryList* m_next;
    CAbstractFactory* m_item;

   public:
    CFactoryList(CAbstractFactory* fact);
    virtual ~CFactoryList(void);
};

/* ctor of CFactoryList, add a class factory to list */
inline CFactoryList::CFactoryList(CAbstractFactory* fact) : m_item(fact) {
    m_next = _head;
    _head = this;
}

#if defined(_MSC_VER)
/* disable warning for the following line : factory( void ): m_item( this ) {}
 */
#pragma warning(disable : 4355)
#endif

/* realization of class factory */
template <class t>
class CFactory : public CAbstractFactory {
    static t _object;
    CFactoryList m_item;

   public:
    /* add itself to list of class factory when constructed */
    CFactory(void) : m_item(this) {}

    virtual ~CFactory() {}

    /* create object of this class if matched */
    void* Create(const char* class_name) {
        std::string strClassName;

#if defined(WIN32)
        strClassName = ("class ");
#else
        char szSize[4] = {0};
        sprintf(szSize, "%d", (int)strlen(class_name));
        strClassName = szSize;
#endif
        strClassName += class_name;

        /* RTTI support */
        return !strcmp(typeid(_object).name(), strClassName.c_str())
                   ? (void*)(new t)
                   : 0;
    }
};
}  // namespace DYN_CLASS
#endif /* __DYNAMIC_H__ */
