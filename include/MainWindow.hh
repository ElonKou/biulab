#pragma once
#ifndef MAIN_WINDOW_H_
#define MAIN_WINDOW_H_

#include "Base.hh"
#include "MainWindow.hh"
#include "Menu.hh"
#include "ModulesManager.hh"
#include "PluginHelper.hh"
#include "WindowBase.hh"

using namespace std;

class MainWindow {
  private:
    GLFWwindow* window;

    Menu menu;

    ModulesManager modules_manager;

    CPluginHelper pluginhelper;

    struct WindowInfo {
        int width;

        int height;

        float font_size;

        string title;

        string fonts_path;

        ImVec4 background_color;
    } main_window_info;

  public:
    MainWindow();

    ~MainWindow();

    GLFWwindow* InitWindow();

    void DrawWindow();

    void StartWindow();

    void SetGL(GLFWwindow* window);

    void LoadFont();

    void ShowDcokSpace();

    void ShowDisabledMessage();

    void SetDarkTheme();

    static void OnKeyBack(GLFWwindow* window, int key, int scanmode, int action, int mode);
};

#endif
