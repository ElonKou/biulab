//++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// File:  lib.cpp
// Author :elonkou
// E-mail :elonkou@ktime.cc
// Date   :Mon 30 Apr 2018 11:21:21 PM CST
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#include "lib.h"
#include <cstdio>
#include <iostream>

using namespace std;

char* getChar(string str) {
    char* dst = new char[255];
    int i = 0;
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
void printOk(int str) {
    printf("%d", str);
}

void printWaning(string str) {
    char* dst = getChar(str);
    printf(BROWN "%s" NONE, dst);
    delete dst;
}
void printWaning(int str) {
    printf(BROWN "%d" NONE, str);
}

void printSucceed(string str) {
    char* dst = getChar(str);
    printf(GREEN "%s" NONE, dst);
    delete dst;
}

void printSucceed(int str) {
    printf(GREEN "%d" NONE, str);
}

void printError(string str) {
    char* dst = getChar(str);
    printf(RED "%s" NONE, dst);
    delete dst;
}
void printError(int str) {
    printf(RED "%d" NONE, str);
}

void printSome(string str) {
    char* dst = getChar(str);
    printf(PURPLE "%s" NONE, dst);
    delete dst;
}
void printSome(int str) {
    printf(PURPLE "%d" NONE, str);
}

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