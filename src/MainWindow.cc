/*================================================================
*  Copyright (C)2019 All rights reserved.
*  FileName : MainWindow.cc
*  Author   : elonkou
*  Email    : elonkou@ktime.cc
*  Date     : 2019年12月21日 星期六 17时59分01秒
================================================================*/

#include "MainWindow.hh"

MainWindow::MainWindow() {
    main_window_info.fonts_path = "../resources/fonts/YaHei.Consolas.1.12.ttf";
    main_window_info.font_size = 18.0f;
    main_window_info.background_color = ImVec4(0.12, 0.12, 0.12, 1.0);

    window = initWindow();

    pluginhelper.Load("/home/elonkou/ELONKOU/03.BIULAB/biulab/install/lib",
                      "*.so");
    // pluginhelper.Load("/home/elonkou/ELONKOU/03.BIULAB/biulab/modules/BiulabWidget",
    //                   "*.so");
    ov_window = (WindowBase*)pluginhelper.Create("OverviewWindow");

    loadFont();
    setGL(window);
    setDarkTheme();
}

MainWindow::~MainWindow() {}

GLFWwindow* MainWindow::initWindow() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
    glfwWindowHint(GLFW_SAMPLES, 4);
    glEnable(GL_MULTISAMPLE);
    // glEnable(GL_DEPTH_TEST);
    // create window
    GLFWwindow* window = glfwCreateWindow(1280, 720, "Genetic", NULL, NULL);
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
    return window;
}

void MainWindow::drawWindow() {
    // checkState();
    if (show_dock_sapce) {
        showDcokSpace();
    }
    if (show_main_menu_bar) {
        menu.show();
    }
    // if (show_demo_window) {
    //     ImGui::ShowDemoWindow(&show_demo_window);
    // }
    cout << "dasda:" << show_overlay_bar << endl;
    if (show_overlay_bar && ov_window != 0) {
        ov_window->show();
    }
    // if (show_control_window) {
    //     showControlWindow();
    // }
    // if (show_node_window) {
    //     showNodeWindow();
    // }
    // if (show_display_window) {
    //     showDisplayWindow();
    // }
    // if (show_inspector_window) {
    //     showInspector();
    // }
    // if (show_graph_window) {
    //     showGraph();
    // }
    // if (show_editor_window) {
    //     showEditor();
    // }
}

void MainWindow::startWindow() {
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        glfwPollEvents();
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        drawWindow();
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
    }
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
}

void MainWindow::setGL(GLFWwindow* window) {
    glClearColor(0.12, 0.12, 0.12, 1.0);
    const char* glsl_version = "#version 130";
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);
}

void MainWindow::loadFont() {
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    // io.DeltaTime = 1.0f / 30.0f;
    (void)io;
    io.Fonts->AddFontFromFileTTF(
        main_window_info.fonts_path.c_str(), main_window_info.font_size, NULL,
        io.Fonts->GetGlyphRangesChineseSimplifiedCommon());
    io.Fonts->Fonts[0]->DisplayOffset = ImVec2(0, -1);
}

void MainWindow::setDarkTheme() {
    ImGuiStyle* style = &ImGui::GetStyle();
    ImVec4* colors = style->Colors;

    style->WindowPadding = ImVec2(8, 4);
    style->WindowRounding = 0.0f;
    style->WindowBorderSize = 0.0f;
    style->WindowTitleAlign = ImVec2(0.00, 0.37);
    style->FramePadding = ImVec2(5, 3);
    style->FrameRounding = 4.0f;
    style->PopupBorderSize = 0.0f;
    style->ChildBorderSize = 0.0f;
    style->ChildRounding = 0.0f;
    style->ItemSpacing = ImVec2(8, 4);
    style->ItemInnerSpacing = ImVec2(4, 4);
    style->IndentSpacing = 24.0f;
    style->ScrollbarSize = 12.0f;
    style->ScrollbarRounding = 6.0f;
    style->GrabMinSize = 8.0f;
    style->GrabRounding = 2.0f;

    style->DisplaySafeAreaPadding = ImVec2(0.0, 0.0);

    colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
    colors[ImGuiCol_WindowBg] = ImVec4(0.10f, 0.10f, 0.10f, 0.94f);
    colors[ImGuiCol_ChildBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    colors[ImGuiCol_PopupBg] = ImVec4(0.08f, 0.08f, 0.08f, 0.94f);
    colors[ImGuiCol_Border] = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
    colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    colors[ImGuiCol_FrameBg] = ImVec4(0.34f, 0.34f, 0.34f, 0.54f);
    colors[ImGuiCol_FrameBgHovered] = ImVec4(0.62f, 0.63f, 0.63f, 0.40f);
    colors[ImGuiCol_FrameBgActive] = ImVec4(0.54f, 0.54f, 0.54f, 0.67f);
    colors[ImGuiCol_TitleBg] = ImVec4(0.24f, 0.24f, 0.24f, 1.00f);
    colors[ImGuiCol_TitleBgActive] = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
    colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
    colors[ImGuiCol_MenuBarBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
    colors[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.53f);
    colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
    colors[ImGuiCol_CheckMark] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    colors[ImGuiCol_SliderGrab] = ImVec4(0.73f, 0.73f, 0.73f, 1.00f);
    colors[ImGuiCol_SliderGrabActive] = ImVec4(0.86f, 0.86f, 0.86f, 1.00f);
    colors[ImGuiCol_Button] = ImVec4(0.61f, 0.61f, 0.61f, 0.40f);
    colors[ImGuiCol_ButtonHovered] = ImVec4(0.48f, 0.48f, 0.48f, 1.00f);
    colors[ImGuiCol_ButtonActive] = ImVec4(0.63f, 0.63f, 0.63f, 1.00f);
    colors[ImGuiCol_Header] = ImVec4(0.50f, 0.50f, 0.50f, 0.31f);
    colors[ImGuiCol_HeaderHovered] = ImVec4(0.67f, 0.67f, 0.67f, 0.80f);
    colors[ImGuiCol_HeaderActive] = ImVec4(0.63f, 0.63f, 0.64f, 1.00f);
    colors[ImGuiCol_Separator] = ImVec4(0.03f, 0.03f, 0.04f, 0.50f);
    colors[ImGuiCol_SeparatorHovered] = ImVec4(0.03f, 0.03f, 0.04f, 0.78f);
    colors[ImGuiCol_SeparatorActive] = ImVec4(0.04f, 0.04f, 0.05f, 1.00f);
    colors[ImGuiCol_ResizeGrip] = ImVec4(0.50f, 0.51f, 0.52f, 0.25f);
    colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.64f, 0.64f, 0.64f, 0.67f);
    colors[ImGuiCol_ResizeGripActive] = ImVec4(0.68f, 0.68f, 0.68f, 0.95f);
    colors[ImGuiCol_Tab] = ImVec4(0.20f, 0.20f, 0.20f, 0.86f);
    colors[ImGuiCol_TabHovered] = ImVec4(0.37f, 0.37f, 0.38f, 0.80f);
    colors[ImGuiCol_TabActive] = ImVec4(0.34f, 0.34f, 0.34f, 1.00f);
    colors[ImGuiCol_TabUnfocused] = ImVec4(0.43f, 0.43f, 0.43f, 0.97f);
    colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.54f, 0.54f, 0.54f, 1.00f);
    colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
    colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.32f, 0.21f, 1.00f);
    colors[ImGuiCol_PlotHistogram] = ImVec4(0.96f, 0.77f, 0.37f, 1.00f);
    colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.95f, 0.38f, 0.40f, 1.00f);
    colors[ImGuiCol_TextSelectedBg] = ImVec4(0.44f, 0.44f, 0.44f, 0.35f);
    colors[ImGuiCol_DockingPreview] = ImVec4(0.38f, 0.39f, 0.39f, 0.70f);
    colors[ImGuiCol_DragDropTarget] = ImVec4(0.58f, 0.58f, 0.57f, 0.90f);
    colors[ImGuiCol_NavHighlight] = ImVec4(0.80f, 0.80f, 0.80f, 1.00f);
    colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
    colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
    colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
}

void MainWindow::showDcokSpace() {
    static bool opt_fullscreen_persistant = true;
    bool opt_fullscreen = opt_fullscreen_persistant;

    ImGuiWindowFlags window_flags =
        ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
    if (opt_fullscreen) {
        ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->Pos);
        ImGui::SetNextWindowSize(viewport->Size);
        ImGui::SetNextWindowViewport(viewport->ID);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        window_flags |= ImGuiWindowFlags_NoTitleBar |
                        ImGuiWindowFlags_NoCollapse |
                        ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
        window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus |
                        ImGuiWindowFlags_NoNavFocus;
    }

    if (dockspace_flag & ImGuiDockNodeFlags_PassthruCentralNode)
        window_flags |= ImGuiWindowFlags_NoBackground;

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    ImGui::Begin("DockSpace Geneteic", &show_dock_sapce, window_flags);
    ImGui::PopStyleVar();

    if (opt_fullscreen) ImGui::PopStyleVar(2);

    // DockSpace
    ImGuiIO& io = ImGui::GetIO();
    if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable) {
        ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
        ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flag);
    } else {
        showDisabledMessage();
    }

    ImGui::End();
}

void MainWindow::showDisabledMessage() {
    ImGuiIO& io = ImGui::GetIO();
    ImGui::Text("ERROR: Docking is not enabled! See Demo > Configuration.");
    ImGui::Text(
        "Set io.ConfigFlags |= ImGuiConfigFlags_DockingEnable in your code, "
        "or ");
    ImGui::SameLine(0.0f, 0.0f);
    if (ImGui::SmallButton("click here"))
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
}

void MainWindow::key_back(GLFWwindow* window, int key, int scanmode, int action,
                          int mode) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
    // if (key == GLFW_KEY_C && action == GLFW_PRESS) {
    //     show_control_window = !show_control_window;
    // }
    // if (key == GLFW_KEY_D && action == GLFW_PRESS) {
    //     show_display_window = !show_display_window;
    // }
}