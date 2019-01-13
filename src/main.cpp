//++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// File   :main.cpp
// Author :elonkou
// E-mail :elonkou@ktime.cc
// Date   :Mon 07 Jan 2019 05:33:32 PM CST
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "core_genetic.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
using namespace std;

void key_back(GLFWwindow* window, int key, int scanmode, int action, int mode) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
}
int main() {
    // Controller con;
    // con.loop();
    // con.print();
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
    glfwWindowHint(GLFW_SAMPLES, 4);
    glEnable(GL_MULTISAMPLE);
    // glEnable(GL_DEPTH_TEST);
    // create window
    GLFWwindow* window = glfwCreateWindow(800, 600, "Hello", NULL, NULL);
    glfwMakeContextCurrent(window);
    // callback function
    glfwSetKeyCallback(window, key_back);
    // glew
    glewExperimental = GL_TRUE;
    glewInit();
    // glViewport
    int height, width;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);
    // 创建窗口对象
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    (void)io;
    io.Fonts->AddFontFromFileTTF(
        "./fonts/YaHei.Consolas.1.12.ttf", 21.0f, NULL,
        io.Fonts->GetGlyphRangesChineseSimplifiedCommon());
    //
    const char* glsl_version = "#version 130";
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);
    ImGui::StyleColorsDark();
    bool my_tool_active = true;
    // 绘制
    glClearColor(0.12, 0.12, 0.12, 1.0);
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        //
        // glUseProgram(shaderProgram);
        // glBindVertexArray(VAO);
        // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        // glBindVertexArray(0);
        // glfwMakeContextCurrent(window);
        // glfwSwapBuffers(window);
        // 绘制窗口
        ImGui::Begin("Tools", &my_tool_active, 0);
        ImGui::Text("Hello from another window!");
        ImGui::Text("Hello, world %d", 123);
        if (ImGui::Button("Save我是")) {
            // do stuff
        }
        ImGui::End();
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    // glDeleteVertexArrays(1, &VAO);
    // glDeleteBuffers(1, &VBO);
    // glDeleteBuffers(1, &EBO);
    glfwTerminate();
    return 0;
}
