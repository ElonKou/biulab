#pragma once
#ifndef MAIN_WINDOW_H_
#define MAIN_WINDOW_H_

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include "MainWindow.hh"
#include "BiuLab.hh"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

using namespace std;

namespace BiuLab {
namespace Window {

class MainWindow {
   private:
    GLFWwindow* window;

    int width;

    int height;

    string title;

   public:
    MainWindow();

    ~MainWindow();

    GLFWwindow* initWindow();

    void drawWindow();

    void startWindow();

    void loadFont();

    void setGL(GLFWwindow* window);

    void showDcokSpace();

    void showDisabledMessage();

    void setDarkTheme();
};

}  // namespace Window
}  // namespace BiuLab

#endif
