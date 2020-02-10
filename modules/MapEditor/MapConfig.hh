#pragma once
#ifndef MAP_CONFIG_H_
#define MAP_CONFIG_H_

class MapConfig {
  private:
  public:
    static bool show_overlay_window;
    static bool show_control_window;
    static bool show_display_window;
    static bool show_graph_window;
    static bool show_mapeditor_window;
    static bool show_node_window;
    static bool show_inspector_window;
    MapConfig();
    ~MapConfig();
};

#endif