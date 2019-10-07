#pragma once
#ifndef MAP_CONFIG_H_
#define MAP_CONFIG_H_

#include "ConfigBase.hh"

class MapConfig : virtual public ConfigBase {
   private:
   public:
    static bool show_overlay_bar;
    static bool show_control_window;
    static bool show_display_window;
    static bool show_graph_window;
    static bool show_editor_window;
    static bool show_node_window;
    static bool show_inspector_window;
    MapConfig();
    ~MapConfig();
};

#endif