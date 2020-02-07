/*================================================================
*  Copyright (C)2019 All rights reserved.
*  FileName : Lib.cc
*  Author   : elonkou
*  Email    : elonkou@ktime.cc
*  Date     : 2019年10月02日 星期三 11时40分13秒
================================================================*/

#include "Lib.hh"
#include <cstdio>
#include <dirent.h>
#include <iostream>
#include <sstream>
#include <string>
#include <sys/time.h>
#include <vector>

using namespace std;

char* GetChar(string str) {
    char* dst = new char[255];
    int   i   = 0;
    for (; i < str.length(); i++) {
        dst[i] = str[i];
    }
    dst[i] = '\0';
    return dst;
}

void PrintOk(string str) {
    char* dst = GetChar(str);
    printf("%s", dst);
    delete dst;
}

void PrintOk(int str) { printf("%d", str); }

void PrintWaning(string str) {
    char* dst = GetChar(str);
    printf(BROWN "%s" NONE, dst);
    delete dst;
}
void PrintWaning(int str) { printf(BROWN "%d" NONE, str); }

void PrintSucceed(string str) {
    char* dst = GetChar(str);
    printf(GREEN "%s" NONE, dst);
    delete dst;
}

void PrintSucceed(int str) { printf(GREEN "%d" NONE, str); }

void PrintError(string str) {
    char* dst = GetChar(str);
    printf(RED "%s" NONE, dst);
    delete dst;
}
void PrintError(int str) { printf(RED "%d" NONE, str); }

void PrintSome(string str) {
    char* dst = GetChar(str);
    printf(PURPLE "%s" NONE, dst);
    delete dst;
}
void PrintSome(int str) { printf(PURPLE "%d" NONE, str); }

vector<string> GetFiles(string dir) {
    vector<string> files;
    DIR*           dp = opendir(dir.c_str());
    struct dirent* dirp;
    while ((dirp = readdir(dp)) != NULL) {
        if (string(dirp->d_name) == "." || string(dirp->d_name) == "..") {
            continue;
        }
        files.push_back(string(dirp->d_name));
    }
    closedir(dp);
    return files;
}

vector<string> Split(const string& s, const string& seperator) {
    std::vector<string>       result;
    typedef string::size_type string_size;
    string_size               i = 0;

    while (i != s.size()) {
        int flag = 0;
        while (i != s.size() && flag == 0) {
            flag = 1;
            for (string_size x = 0; x < seperator.size(); ++x)
                if (s[i] == seperator[x]) {
                    ++i;
                    flag = 0;
                    break;
                }
        }
        flag          = 0;
        string_size j = i;
        while (j != s.size() && flag == 0) {
            for (string_size x = 0; x < seperator.size(); ++x)
                if (s[j] == seperator[x]) {
                    flag = 1;
                    break;
                }
            if (flag == 0)
                ++j;
        }
        if (i != j) {
            result.push_back(s.substr(i, j - i));
            i = j;
        }
    }
    return result;
}
string& Replace_all(string& str, const string& old_value,
                    const string& new_value) {
    while (true) {
        string::size_type pos(0);
        if ((pos = str.find(old_value)) != string::npos)
            str.replace(pos, old_value.length(), new_value);
        else
            break;
    }
    return str;
}

int RandomInt(int range) {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    srand(tv.tv_usec);
    return Random(range);
}

float RandomFloat() { return RandomInt(1000000) * 1.0 / 1000000; }
