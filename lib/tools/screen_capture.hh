#pragma once

// ImGui Screenshot Maker (OpenGL only)
#ifndef SCREEN_CAPTURE_H_
#define SCREEN_CAPTURE_H_

#define _CRT_SECURE_NO_WARNINGS
#include "imgui.h"
#define IMGUI_DEFINE_MATH_OPERATORS
#include "imgui_internal.h"

#include <GLFW/glfw3.h>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

// Helper class for simple bitmap manipulation (not particularly efficient!)
class ImageBuf {
  public:
    typedef unsigned int u32;
    int                  Width, Height;
    u32*                 Data;

    ImageBuf();

    ~ImageBuf();

    void Clear();

    void CreateEmpty(int w, int h);

    void CreateFromCaptureGL(int x, int y, int w, int h);

    void SaveFile(const char* filename);

    void RemoveAlpha();

    void BlitTo(ImageBuf* dst, int src_x, int src_y, int dst_x, int dst_y, int w, int h);

    void FlipVertical();

    u32* GetPtr(int x, int y) {
        return &Data[x + y * Width];
    }
    u32 GetPixel(int x, int y) const {
        return Data[x + y * Width];
    }
};

class ScreenshotMaker {
  public:
    ImGuiStorage Storage;
    float        BorderSize;
    bool         LargePictureMode;
    ImRect       VisibleRect;
    bool         CaptureActive;
    int          CaptureFrame;
    ImRect       CaptureRect;
    int          CaptureLargeOffY;
    ImGuiWindow* CaptureWindow;
    ImageBuf     Output;

    ScreenshotMaker();

    ~ScreenshotMaker();

    void CaptureStart(ImGuiWindow* window);

    void CaptureUpdate();

    void CaptureEnd();

    void Draw(bool* p_open = NULL);
};
#endif