#pragma once
#ifndef BIU_LAB_H_
#define BIU_LAB_H_

#include "BiuLabConfig.hh"
#include "BiuLabTypes.hh"
#include "Lib.hh"
#include "imgui.h"
#include "imgui_biulab_tools.h"
#include "imgui_biulab_widgets.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imgui_internal.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

// modules
extern bool   module_changed;       // whether select the load module panel.
extern bool   module_selected;      // flag for load/close module.
extern string module_selected_name; // the name of module.

// windows
extern bool show_dock_sapce;
extern bool show_main_window;
extern bool show_demo_window;
extern bool show_main_menu_bar;
extern bool show_overlay_window;
extern bool show_control_window;
extern bool show_graph_window;
extern bool show_node_window;
extern bool show_inspector_window;
extern bool show_mapeditor_window;
extern bool show_simplemap_window;
extern bool show_program_window;

// Controller

// Map

// Core

#endif