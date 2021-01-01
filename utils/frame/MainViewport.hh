#pragma once
#ifndef MAIN_WINDOW_HH_
#define MAIN_WINDOW_HH_

#include "Base.hh"
#include "MainViewport.hh"
#include "Menu.hh"
#include "ModuleWindow.hh"
#include "ModulesManager.hh"
#include "PluginHelper.hh"
#include "WindowBase.hh"

using namespace std;

class MainViewport {
  public:
    GLFWwindow* window;

    Menu menu;

    ModuleWindow modules_window;

    ModulesManager* manager;

    struct WindowInfo {
        int width;

        int height;

        float font_size;

        string title;

        string fonts_path;

        ImVec4 background_color;
    } main_window_info;

    MainViewport();

    ~MainViewport();

    GLFWwindow* InitWindow();

    void DrawWindow();

    void StartWindow();

    void SetGL(GLFWwindow* window);

    void SetIcon(GLFWwindow* window);

    void LoadFont();

    void ShowDcokSpace();

    void ShowDisabledMessage();

    void SetDarkTheme();

    static void OnKeyBack(GLFWwindow* window, int key, int scanmode, int key_action, int mode);
};

#endif
