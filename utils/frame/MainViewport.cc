/*================================================================
*  Copyright (C)2019 All rights reserved.
*  FileName : MainViewport.cc
*  Author   : elonkou
*  Email    : elonkou@ktime.cc
*  Date     : 2019年12月21日 星期六 17时59分01秒
================================================================*/

#include "MainViewport.hh"
#include "imgui_biulab_tools.h"

MainViewport::MainViewport() {
}

MainViewport::MainViewport(ModulesManager* man) {
    main_window_info.fonts_path       = BIULAB_INSTALL_PATH "/../resources/fonts/YaHei.Consolas.1.12.ttf";
    main_window_info.font_size        = 18.0f;
    main_window_info.background_color = ImVec4(0.12, 0.12, 0.12, 1.0);

    window = InitWindow();
    LoadFont();
    SetGL(window);
    SetDarkTheme();
    manager        = man;
    menu           = new Menu(man);
    modules_window = new ModuleWindow(man);
}

MainViewport::~MainViewport() {}

GLFWwindow* MainViewport::InitWindow() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
    glfwWindowHint(GLFW_SAMPLES, 4);
    glEnable(GL_MULTISAMPLE);
    GLFWwindow* window = glfwCreateWindow(1280, 720, "BiuLab " BIULAB_VERSION " © elonkou", NULL, NULL);
    SetIcon(window);
    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, OnKeyBack);
    glewExperimental = GL_TRUE;
    glewInit();
    int height, width;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);
    return window;
}

void MainViewport::Show() {
    ShowDcokSpace();
    if (manager->options.show_menu_bar) {
        menu->Show();
    }
    if (manager->options.show_program_window) {
        modules_window->Show();
    }
    manager->UpdateModule();
}

void MainViewport::StartWindow() {
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        glfwPollEvents();
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        Show();
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
    }
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
}

void MainViewport::SetGL(GLFWwindow* window) {
    glClearColor(0.12, 0.12, 0.12, 1.0);
    const char* glsl_version = "#version 130";
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);
}

void MainViewport::SetIcon(GLFWwindow* window_) {
#if GLFW_VERSION_MAJOR * 1000 + GLFW_VERSION_MINOR * 100 >= 3200
    /* The function glfwSetWindowIcon only display icon on verison 3.2+. */
    GLFWimage images[2];
    int       iw, ih;
    string    icon_path       = BIULAB_INSTALL_PATH "/resources/icons/icon.png";
    string    icon_small_path = BIULAB_INSTALL_PATH "/resources/icons/icon_small.png";
    images[0].pixels          = stbi_load(icon_path.c_str(), &iw, &ih, NULL, 4);
    images[0].width           = iw;
    images[0].height          = ih;
    images[1].pixels          = stbi_load(icon_small_path.c_str(), &iw, &ih, NULL, 4);
    images[1].width           = iw;
    images[1].height          = ih;
    glfwSetWindowIcon(window_, 2, images);
    stbi_image_free(images[0].pixels);
    stbi_image_free(images[1].pixels);
#endif
}

void MainViewport::LoadFont() {
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    (void)io;
    io.Fonts->AddFontFromFileTTF(main_window_info.fonts_path.c_str(), main_window_info.font_size, NULL, io.Fonts->GetGlyphRangesChineseSimplifiedCommon());
    io.Fonts->Fonts[0]->DisplayOffset = ImVec2(0, -1);
}

void MainViewport::SetDarkTheme() {
    ImGuiStyle* style  = &ImGui::GetStyle();
    ImVec4*     colors = style->Colors;

    style->WindowPadding     = ImVec2(8, 4);
    style->WindowRounding    = 0.0f;
    style->WindowBorderSize  = 0.0f;
    style->WindowTitleAlign  = ImVec2(0.00, 0.37);
    style->FramePadding      = ImVec2(5, 3);
    style->FrameRounding     = 4.0f;
    style->PopupBorderSize   = 0.0f;
    style->ChildBorderSize   = 0.0f;
    style->ChildRounding     = 0.0f;
    style->ItemSpacing       = ImVec2(6, 4);
    style->ItemInnerSpacing  = ImVec2(4, 4);
    style->IndentSpacing     = 16.0f;
    style->ScrollbarSize     = 10.0f;
    style->ScrollbarRounding = 6.0f;
    style->GrabMinSize       = 8.0f;
    style->GrabRounding      = 2.0f;

    style->DisplaySafeAreaPadding = ImVec2(0.0, 0.0);

    colors[ImGuiCol_Text]                  = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    colors[ImGuiCol_Text]                  = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    colors[ImGuiCol_TextDisabled]          = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
    colors[ImGuiCol_WindowBg]              = ImVec4(0.10f, 0.10f, 0.10f, 0.94f);
    colors[ImGuiCol_ChildBg]               = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    colors[ImGuiCol_PopupBg]               = ImVec4(0.08f, 0.08f, 0.08f, 0.94f);
    colors[ImGuiCol_Border]                = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
    colors[ImGuiCol_BorderShadow]          = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    colors[ImGuiCol_FrameBg]               = ImVec4(0.34f, 0.34f, 0.34f, 0.54f);
    colors[ImGuiCol_FrameBgHovered]        = ImVec4(0.62f, 0.63f, 0.63f, 0.40f);
    colors[ImGuiCol_FrameBgActive]         = ImVec4(0.54f, 0.54f, 0.54f, 0.67f);
    colors[ImGuiCol_TitleBg]               = ImVec4(0.24f, 0.24f, 0.24f, 1.00f);
    colors[ImGuiCol_TitleBgActive]         = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
    colors[ImGuiCol_TitleBgCollapsed]      = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
    colors[ImGuiCol_MenuBarBg]             = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
    colors[ImGuiCol_ScrollbarBg]           = ImVec4(0.02f, 0.02f, 0.02f, 0.53f);
    colors[ImGuiCol_ScrollbarGrab]         = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabHovered]  = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabActive]   = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
    colors[ImGuiCol_CheckMark]             = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    colors[ImGuiCol_CheckMark]             = ImVec4(0.88f, 0.88f, 0.88f, 1.00f);
    colors[ImGuiCol_SliderGrab]            = ImVec4(0.73f, 0.73f, 0.73f, 1.00f);
    colors[ImGuiCol_SliderGrabActive]      = ImVec4(0.86f, 0.86f, 0.86f, 1.00f);
    colors[ImGuiCol_Button]                = ImVec4(0.61f, 0.61f, 0.61f, 0.40f);
    colors[ImGuiCol_ButtonHovered]         = ImVec4(0.48f, 0.48f, 0.48f, 1.00f);
    colors[ImGuiCol_ButtonActive]          = ImVec4(0.63f, 0.63f, 0.63f, 1.00f);
    colors[ImGuiCol_Header]                = ImVec4(0.50f, 0.50f, 0.50f, 0.31f);
    colors[ImGuiCol_HeaderHovered]         = ImVec4(0.67f, 0.67f, 0.67f, 0.80f);
    colors[ImGuiCol_HeaderActive]          = ImVec4(0.63f, 0.63f, 0.64f, 1.00f);
    colors[ImGuiCol_Separator]             = ImVec4(0.03f, 0.03f, 0.04f, 0.50f);
    colors[ImGuiCol_SeparatorHovered]      = ImVec4(0.03f, 0.03f, 0.04f, 0.78f);
    colors[ImGuiCol_SeparatorActive]       = ImVec4(0.04f, 0.04f, 0.05f, 1.00f);
    colors[ImGuiCol_ResizeGrip]            = ImVec4(0.50f, 0.51f, 0.52f, 0.25f);
    colors[ImGuiCol_ResizeGripHovered]     = ImVec4(0.64f, 0.64f, 0.64f, 0.67f);
    colors[ImGuiCol_ResizeGripActive]      = ImVec4(0.68f, 0.68f, 0.68f, 0.95f);
    colors[ImGuiCol_Tab]                   = ImVec4(0.20f, 0.20f, 0.20f, 0.86f);
    colors[ImGuiCol_TabHovered]            = ImVec4(0.37f, 0.37f, 0.38f, 0.80f);
    colors[ImGuiCol_TabActive]             = ImVec4(0.34f, 0.34f, 0.34f, 1.00f);
    colors[ImGuiCol_TabUnfocused]          = ImVec4(0.43f, 0.43f, 0.43f, 0.97f);
    colors[ImGuiCol_TabUnfocusedActive]    = ImVec4(0.54f, 0.54f, 0.54f, 1.00f);
    colors[ImGuiCol_PlotLines]             = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
    colors[ImGuiCol_PlotLinesHovered]      = ImVec4(1.00f, 0.32f, 0.21f, 1.00f);
    colors[ImGuiCol_PlotHistogram]         = ImVec4(0.96f, 0.77f, 0.37f, 1.00f);
    colors[ImGuiCol_PlotHistogramHovered]  = ImVec4(0.95f, 0.38f, 0.40f, 1.00f);
    colors[ImGuiCol_TextSelectedBg]        = ImVec4(0.44f, 0.44f, 0.44f, 0.35f);
    colors[ImGuiCol_DockingPreview]        = ImVec4(0.38f, 0.39f, 0.39f, 0.70f);
    colors[ImGuiCol_DragDropTarget]        = ImVec4(0.58f, 0.58f, 0.57f, 0.90f);
    colors[ImGuiCol_NavHighlight]          = ImVec4(0.80f, 0.80f, 0.80f, 1.00f);
    colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
    colors[ImGuiCol_NavWindowingDimBg]     = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
    colors[ImGuiCol_ModalWindowDimBg]      = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
}

void MainViewport::ShowDcokSpace() {
    static bool opt_fullscreen_persistant = true;
    bool        opt_fullscreen            = opt_fullscreen_persistant;

    ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
    if (opt_fullscreen) {
        ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->Pos);
        ImGui::SetNextWindowSize(viewport->Size);
        ImGui::SetNextWindowViewport(viewport->ID);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
        window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
    }
    ImGuiDockNodeFlags dockspace_flag = ImGuiDockNodeFlags_None | ImGuiDockNodeFlags_PassthruCentralNode | ImGuiDockNodeFlags_NoWindowMenuButton;
    if (dockspace_flag & ImGuiDockNodeFlags_PassthruCentralNode)
        window_flags |= ImGuiWindowFlags_NoBackground;

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    ImGui::Begin("Biulab DockSpace", &manager->options.show_dock_space, window_flags);
    ImGui::PopStyleVar();

    if (opt_fullscreen)
        ImGui::PopStyleVar(2);

    // DockSpace
    ImGuiIO& io = ImGui::GetIO();
    if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable) {
        ImGuiID dockspace_id = ImGui::GetID("BiulabDockSpace");
        ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flag);
    } else {
        ShowDisabledMessage();
    }

    ImGui::End();
}

void MainViewport::ShowDisabledMessage() {
    ImGuiIO& io = ImGui::GetIO();
    ImGui::Text("ERROR: Docking is not enabled! See Demo > Configuration.");
    ImGui::Text(
        "Set io.ConfigFlags |= ImGuiConfigFlags_DockingEnable in your code, "
        "or ");
    ImGui::SameLine(0.0f, 0.0f);
    if (ImGui::SmallButton("click here"))
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
}

void MainViewport::OnKeyBack(GLFWwindow* window, int key, int scanmode, int key_action, int mode) {
    if (key == GLFW_KEY_ESCAPE && key_action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
    // if (key == GLFW_KEY_C && key_action == GLFW_PRESS) {
    //     show_control_window = !show_control_window;
    // }
    // if (key == GLFW_KEY_D && key_action == GLFW_PRESS) {
    //     show_display_window = !show_display_window;
    // }
}
