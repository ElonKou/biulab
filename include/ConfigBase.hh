#pragma once
#ifndef CONFIG_BASE_H_
#define CONFIG_BASE_H_

class ConfigBase {
   private:
   public:
    static bool show_dock_sapce;
    static bool show_main_window;
    static bool show_demo_window;
    static bool show_main_menu_bar;
    ConfigBase();
    ~ConfigBase();
};

#endif