/*================================================================
*  Copyright (C)2020 All rights reserved.
*  FileName : imgui_biulab_tools.cpp
*  Author   : elonkou
*  Email    : elonkou@ktime.cc
*  Date     : 2020年02月14日 星期五 11时13分52秒
================================================================*/

#include "imgui_biulab_tools.h"
#include "stb_image.h"

vec_2i ImGuiVec2vec_2i(ImVec2& v) {
    return vec_2i(int(v.x), int(v.y));
}

bool LoadTextureFromFile(const char* filename, GLuint* out_texture, int* out_width, int* out_height) {
    // Load from file
    int            image_width  = 0;
    int            image_height = 0;
    unsigned char* image_data   = stbi_load(filename, &image_width, &image_height, NULL, 4);
    if (image_data == NULL)
        return false;

    // Create a OpenGL texture identifier
    GLuint image_texture;
    glGenTextures(1, &image_texture);
    glBindTexture(GL_TEXTURE_2D, image_texture);

    // Setup filtering parameters for display
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Upload pixels into texture
    glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image_width, image_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);
    stbi_image_free(image_data);

    *out_texture = image_texture;
    *out_width   = image_width;
    *out_height  = image_height;

    return true;
}