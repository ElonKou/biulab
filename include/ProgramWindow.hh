#pragma once
#ifndef PROGRAMM_WINDOW_H_
#define PROGRAMM_WINDOW_H_

#include "BiuLab.hh"
#include "BiuLabConfig.hh"
#include "ModulesManager.hh"
#include "WindowBase.hh"
#include "fstream"

typedef struct ProgramWindowData {
    string         program_info;
    string         program_name;
    string         program_icon;
    vector<string> dependences;
    GLuint         tex_id;
    ImVec2         size;
} ProgramWindowData;

class ProgramWindow : public WindowBase {
  public:
    vector<ProgramWindowData> data;

    ModulesManager* manager;

    ProgramWindow();

    ~ProgramWindow();

    virtual void Show();

    virtual void UpdateData();
};

#endif
