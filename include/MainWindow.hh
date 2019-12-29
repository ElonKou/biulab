#pragma once
#ifndef MAIN_WINDOW_H_
#define MAIN_WINDOW_H_

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include "BiuLab.hh"
#include "MainWindow.hh"
#include "Menu.hh"
#include "ModulesManager.hh"
#include "PluginHelper.hh"
#include "imgui.h"
#include "WindowBase.hh"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imgui_internal.h"

using namespace std;
// using namespace BiuLab::Widget;

class MainWindow {
   private:
    GLFWwindow* window;

    Menu menu;

    ModulesManager manager;

    // WindowBase* overview_window;
    // WindowBase* inspect_window;
    // WindowBase* mapeditor_window;
    // WindowBase* simmap_window;

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

    GLFWwindow* initWindow();

    void drawWindow();

    void startWindow();

    void setGL(GLFWwindow* window);

    void loadFont();

    void showDcokSpace();

    void showDisabledMessage();

    void setDarkTheme();

    static void key_back(GLFWwindow* window, int key, int scanmode, int action,
                         int mode);
};

#endif
