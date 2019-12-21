project(biulab)
cmake_minimum_required(VERSION 2.8)
add_definitions(-std=c++11)

aux_source_directory(./src BIULAB_SRC)
aux_source_directory(./lib/frame BIULAB_SRC)
aux_source_directory(./lib/imgui BIULAB_SRC)
aux_source_directory(./base BIULAB_SRC)

MESSAGE(${BIULAB_SRC})

include_directories(
    include
    lib/imgui
)

add_executable(biulab ${BIULAB_SRC})
target_link_libraries(biulab glfw dl GLEW GL)