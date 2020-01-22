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

char* getChar(string str) {
    char* dst = new char[255];
    int   i   = 0;
    for (; i < str.length(); i++) {
        dst[i] = str[i];
    }
    dst[i] = '\0';
    return dst;
}

void printOk(string str) {
    char* dst = getChar(str);
    printf("%s", dst);
    delete dst;
}
void printOk(int str) { printf("%d", str); }

void printWaning(string str) {
    char* dst = getChar(str);
    printf(BROWN "%s" NONE, dst);
    delete dst;
}
void printWaning(int str) { printf(BROWN "%d" NONE, str); }

void printSucceed(string str) {
    char* dst = getChar(str);
    printf(GREEN "%s" NONE, dst);
    delete dst;
}

void printSucceed(int str) { printf(GREEN "%d" NONE, str); }

void printError(string str) {
    char* dst = getChar(str);
    printf(RED "%s" NONE, dst);
    delete dst;
}
void printError(int str) { printf(RED "%d" NONE, str); }

void printSome(string str) {
    char* dst = getChar(str);
    printf(PURPLE "%s" NONE, dst);
    delete dst;
}
void printSome(int str) { printf(PURPLE "%d" NONE, str); }

// printf("[%2u]" BLACK "BLACK " L_BLACK "L_BLACK\n" NONE, __LINE__);
// printf("[%2u]" RED "RED " L_RED "L_RED\n" NONE, __LINE__);
// printf("[%2u]" GREEN "GREEN " L_GREEN "L_GREEN\n" NONE, __LINE__);
// printf("[%2u]" BROWN "BROWN " YELLOW "YELLOW\n" NONE, __LINE__);
// printf("[%2u]" BLUE "BLUE " L_BLUE "L_BLUE\n" NONE, __LINE__);
// printf("[%2u]" PURPLE "PURPLE " L_PURPLE "L_PURPLE\n" NONE, __LINE__);
// printf("[%2u]" CYAN "CYAN " L_CYAN "L_CYAN\n" NONE, __LINE__);
// printf("[%2u]" GRAY "GRAY " WHITE "WHITE\n" NONE, __LINE__);
// printf("[%2u]\e[1;31;40m Red \e[0m\n", __LINE__);
// printf("[%2u]" BOLD "BOLD\n" NONE, __LINE__);
// printf("[%2u]" UNDERLINE "UNDERLINE\n" NONE, __LINE__);
// printf("[%2u]" BLINK "BLINK\n" NONE, __LINE__);
// printf("[%2u]" REVERSE "REVERSE\n" NONE, __LINE__);

vector<string> getFiles(string dir) {
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

vector<string> split(const string& s, const string& seperator) {
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
string& replace_all(string& str, const string& old_value,
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

int randomInt(int range) {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    srand(tv.tv_usec);
    return random(range);
}

float randomFloat() { return randomInt(1000000) * 1.0 / 1000000; }
