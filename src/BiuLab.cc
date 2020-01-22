#include "BiuLab.hh"

bool               show_dock_sapce       = true;
bool               show_main_window      = true;
bool               show_demo_window      = false;
bool               show_main_menu_bar    = true;
bool               show_overlay_bar      = true;
bool               show_control_window   = true;
bool               show_graph_window     = true;
bool               show_editor_window    = true;
bool               show_node_window      = false;
bool               show_inspector_window = true;
bool               show_mapeditor_window = true;
bool               show_simplemap_window = true;
ImGuiDockNodeFlags dockspace_flag        = ImGuiDockNodeFlags_None | ImGuiDockNodeFlags_PassthruCentralNode | ImGuiDockNodeFlags_NoWindowMenuButton;
