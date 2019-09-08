#ifndef INIT_WINDOW
#define INIT_WINDOW

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#define WIN_WIDTH 1280
#define WIN_HEIGHT 720

class windowView {
   public:
    GLFWwindow* window;

    static bool show_dock_sapce;
    static bool show_main_window;
    static bool show_demo_window;
    static bool show_main_menu_bar;
    static bool show_overlay_bar;
    static bool show_control_window;
    static bool show_display_window;
    static bool show_graph_window;
    static bool show_node_window;
    static bool show_inspector_window;

    static ImGuiDockNodeFlags dockspace_flags;

    windowView();
    ~windowView();

    void drawWindow();

    GLFWwindow* initWindow();
    void loadFont();
    void setGL(GLFWwindow* window);
    void setWhiteTheme();
    void setDarkTheme();
    void setNewTheme();

    void showMenuFile();
    void showMainMenuBar();
    void showControlWindow();
    void showDisplayWindow();
    void showNodeWindow();
    void showOverlay();
    void showInspector();
    void showGraph();
   //  void showMainWindow();

    void showDcokSpace();
    void showDisabledMessage();
    void showHelpMarker(const char* desc);

    static void key_back(GLFWwindow* window, int key, int scanmode, int action,
                         int mode);
};

#endif