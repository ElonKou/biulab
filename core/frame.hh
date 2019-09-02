#ifndef INIT_WINDOW
#define INIT_WINDOW

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#define WIN_WIDTH 1280
#define WIN_HEIGHT 720

GLFWwindow* init_window();
void load_font();
void set_GL(GLFWwindow* window);
void set_white_theme();
void set_dark_theme();
void set_new_theme();

void ShowMenuFile();
void ShowMainMenuBar();
void ShowOverlay(bool* p_open);
void ShowHelpMarker(const char* desc);
#endif