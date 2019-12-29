cmake_minimum_required(VERSION 2.8)
add_definitions(-std=c++11)
set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR}/../install)

# [build]
include_directories(
    ./
    ../include
    ../lib/imgui
    ../lib/tools
    ../lib/frame
)

add_subdirectory(BiulabWidget)

# add_subdirectory(Robbie)

# add_subdirectory(MapEditor)

add_subdirectory(SimpleMap)

# [install]
# install(DIRECTORY BiulabWidget  
#     DESTINATION ${CMAKE_INSTALL_PREFIX}/BiulabWidget
#     FILES_MATCHING PATTERN "*.h" PATTERN "*.hh"
#     PERMISSIONS OWNER_WRITE OWNER_READ GROUP_READ GROUP_WRITE WORLD_READ
# )