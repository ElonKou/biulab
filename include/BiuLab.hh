#pragma once
#ifndef BIU_LAB_H_
#define BIU_LAB_H_

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imgui_internal.h"

// windows

namespace BiuLab {
static bool show_dock_sapce = true;
static bool show_main_window = true;
static bool show_demo_window = false;
static bool show_main_menu_bar = true;
static bool show_overlay_bar = true;
static bool show_control_window = true;
static bool show_display_window = true;
static bool show_graph_window = true;
static bool show_editor_window = true;
static bool show_node_window = false;
static bool show_inspector_window = true;
// static ImGuiDockNodeFlags dockspace_flag;
static ImGuiDockNodeFlags dockspace_flag =
    ImGuiDockNodeFlags_None | ImGuiDockNodeFlags_PassthruCentralNode |
    ImGuiDockNodeFlags_NoWindowMenuButton;

}  // namespace BiuLab

// Controller

// Map

// Core

#endif