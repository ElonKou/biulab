#pragma once
#ifndef INIT_WINDOW
#define INIT_WINDOW

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include "MapEditor.hh"
#include "RobbieController.hh"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#define WIN_WIDTH 1280
#define WIN_HEIGHT 720

using namespace std;

class windowView {
   public:
    GLFWwindow* window;
    Controller* con;
    MapEditor* mapEditor;
    RobbieMap* map;
    // inspector
    string ins_robbie_path;
    string ins_map_path;
    string ins_select_robbie;
    string ins_select_map;
    bool has_map;
    bool map_changed;
    bool has_rob;
    bool rob_changed;

    static bool show_dock_sapce;
    static bool show_main_window;
    static bool show_demo_window;
    static bool show_main_menu_bar;
    static bool show_overlay_bar;
    static bool show_control_window;
    static bool show_display_window;
    static bool show_graph_window;
    static bool show_editor_window;
    static bool show_node_window;
    static bool show_inspector_window;

    static ImGuiDockNodeFlags dockspace_flags;

    windowView();
    windowView(Controller* con_ptr);
    ~windowView();

    GLFWwindow* initWindow();
    void drawWindow();
    void startWindow();
    void loadFont();
    void setGL(GLFWwindow* window);
    void setWhiteTheme();
    void setDarkTheme();
    void setNewTheme();
    void setController(Controller* con_ptr);
    void setMap(RobbieMap* map);

    void showMenuFile();
    void showMainMenuBar();
    void showControlWindow();
    void showDisplayWindow();
    void showNodeWindow();
    /* overview */
    void showOverlay();
    void showInspector();
    void showGraph();
    void showEditor();
    //  void showMainWindow();

    void showDcokSpace();
    void showDisabledMessage();
    void showHelpMarker(const char* desc);

    void checkState();
    static void key_back(GLFWwindow* window, int key, int scanmode, int action,
                         int mode);
};

#endif