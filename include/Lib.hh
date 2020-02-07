#pragma once
#ifndef LIB_H_
#define LIB_H_

#define ABS(x) (x > 0 ? x : -x)
#define MAX(x, y) (x > y ? x : y)
#define MIN(x, y) (x < y ? x : y)

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
#define Random(x) (rand() % x);

char* GetChar(string str);

void PrintOk(string str);

void PrintOk(int str);

void PrintWaning(string str);

void PrintWaning(int str);

void PrintSucceed(string str);

void PrintSucceed(int str);

void PrintError(string str);

void PrintError(int str);

void PrintSome(string str);

void PrintSome(int str);

// File tools

template <class Type>
Type StringToNum(const std::string& str) {
    istringstream iss(str);
    Type          num;
    iss >> num;
    return num;
}

vector<string> GetFiles(string dir);

vector<string> Split(const string& s, const string& seperator);

string& Replace_all(string& str, const string& old_value, const string& new_value);

int RandomInt(int range);

float RandomFloat();

#endif