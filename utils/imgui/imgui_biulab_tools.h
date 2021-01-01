#pragma once
#ifndef IMGUI_BIULAB_TOOLS_H_
#define IMGUI_BIULAB_TOOLS_H_

#include "BiuLab.hh"
#include "imgui.h"
#include <GL/glew.h>
#include <iostream>
#include <stb_image.h>

using namespace std;

#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#endif

vec_2i ImGuiVec2vec_2i(ImVec2& v);

bool LoadTextureFromFile(const char* filename, GLuint* out_texture, int* out_width, int* out_height);

#endif