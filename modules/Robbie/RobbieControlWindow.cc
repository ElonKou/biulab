/*================================================================
*  Copyright (C)2020 All rights reserved.
*  FileName : RobbieControlWindow.cc
*  Author   : elonkou
*  Email    : elonkou@ktime.cc
*  Date     : 2020年02月12日 星期三 00时26分31秒
================================================================*/

#include "RobbieControlWindow.hh"

void RobbieControlWindow::Show() {
    if (ImGui::Begin("Robbie")) {
        {
            // variablesif
            ImGui::Checkbox("Stop check", &robbie_controll->data->train_stop_check);
            ImGui::SameLine();
            ImGui::Checkbox("Only show round", &robbie_controll->data->dis_map->only_show_round);
            ImGui::SameLine();
            showHelpMarker("this will check the stop flag, the controller will stop when robbie dont move.");
            if (ImGui::Button("R##1")) {
                robbie_controll->data->loop_controller = LOOP_CONTROLLER;
            }
            ImGui::SameLine();
            ImGui::SliderInt("Train cnt", &robbie_controll->data->loop_controller, 1, 100000, NULL);
            if (ImGui::Button("R##2")) {
                robbie_controll->data->loop_map = LOOP_MAP;
            }
            ImGui::SameLine();
            ImGui::SliderInt("Train map", &robbie_controll->data->loop_map, 1, 20, NULL);
            if (ImGui::Button("R##3")) {
                robbie_controll->data->robbie_cnt = ROBBIE_CNT;
            }
            ImGui::SameLine();
            ImGui::SliderInt("Robbie cnt", &robbie_controll->data->robbie_cnt, 1, 600, NULL);
            if (ImGui::Button("R##4")) {
                robbie_controll->data->mutate_rate = MUTATE_VAL * 1.0 / MUTATE_ALL;
            }
            ImGui::SameLine();
            ImGui::SliderFloat("Mutate rate", &robbie_controll->data->mutate_rate, 0.0, 1.0, "%.3f%");
            if (ImGui::Button("R##4")) {
                robbie_controll->data->speed = 2;
            }
            ImGui::SameLine();
            ImGui::SliderInt("Play speed", &robbie_controll->data->speed, 1, 120, "%d");
        }
        {
            // controller comand
            if (!robbie_controll->running) {
                if (ImGui::Button("Play")) {
                    robbie_controll->running = true;
                }
            } else {
                if (ImGui::Button("Pause")) {
                    robbie_controll->running = false;
                }
            }
            ImGui::SameLine();
            if (ImGui::Button("Stop")) {
                robbie_controll->running = false;
                robbie_controll->stoped  = true;
            }

            ImGui::SameLine();
            if (ImGui::Button("Train")) {
                cout << "Train" << endl;
            }
            ImGui::SameLine();
            if (ImGui::Button("Step Play")) {
                cout << "Step" << endl;
            }
        }
        ImGui::End();
    }
}
