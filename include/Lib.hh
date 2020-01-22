#pragma once
#ifndef LIB_H_
#define LIB_H_

#ifndef COLOR_PRINT
#define COLOR_PRINT
#define NONE "\e[0m"
#define BLACK "\e[0;30m"
#define L_BLACK "\e[1;30m"
#define RED "\e[0;31m"
#define L_RED "\e[1;31m"
#define GREEN "\e[0;32m"
#define L_GREEN "\e[1;32m"
#define BROWN "\e[0;33m"
#define YELLOW "\e[1;33m"
#define BLUE "\e[0;34m"
#define L_BLUE "\e[1;34m"
#define PURPLE "\e[0;35m"
#define L_PURPLE "\e[1;35m"
#define CYAN "\e[0;36m"
#define L_CYAN "\e[1;36m"
#define GRAY "\e[0;37m"
#define WHITE "\e[1;37m"

#define BOLD "\e[1m"
#define UNDERLINE "\e[4m"
#define BLINK "\e[5m"
#define REVERSE "\e[7m"
#define HIDE "\e[8m"
#define CLEAR "\e[2J"
#define CLRLINE "\r\e[K"
#define CLOSE "\033[0m"
#endif

#include <dirent.h>
#include <sstream>
#include <string>
#include <unistd.h>
#include <vector>

using namespace std;
#define random(x) (rand() % x);

char* getChar(string str);
void  printOk(string str);
void  printOk(int str);
void  printWaning(string str);
void  printWaning(int str);
void  printSucceed(string str);
void  printSucceed(int str);
void  printError(string str);
void  printError(int str);
void  printSome(string str);
void  printSome(int str);

// File tools

template <class Type>
Type stringToNum(const std::string& str) {
    istringstream iss(str);
    Type          num;
    iss >> num;
    return num;
}

vector<string> getFiles(string dir);
vector<string> split(const string& s, const string& seperator);
string&        replace_all(string& str, const string& old_value,
                           const string& new_value);

int   randomInt(int range);
float randomFloat();

#endif