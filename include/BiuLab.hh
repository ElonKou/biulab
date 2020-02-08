#pragma once
#ifndef BIU_LAB_H_
#define BIU_LAB_H_

#include "BiuLabConfig.hh"
#include "BiuLabTypes.hh"
#include "imgui.h"
#include "imgui_biulab.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imgui_internal.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

// windows

extern bool               show_dock_sapce;
extern bool               show_main_window;
extern bool               show_demo_window;
extern bool               show_main_menu_bar;
extern bool               show_overlay_bar;
extern bool               show_control_window;
extern bool               show_graph_window;
extern bool               show_editor_window;
extern bool               show_node_window;
extern bool               show_inspector_window;
extern bool               show_mapeditor_window;
extern bool               show_simplemap_window;
extern ImGuiDockNodeFlags dockspace_flag;

// Controller

// Map

// Core

#endif