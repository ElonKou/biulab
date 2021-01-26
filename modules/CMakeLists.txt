cmake_minimum_required(VERSION 2.8.1)
add_definitions(-std=c++11)
set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR}/../install)

# [config]
# SET(CMAKE_BUILD_TYPE "Debug")
# SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g2 -ggdb")
SET(CMAKE_BUILD_TYPE "Release")
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")

# [build]
include_directories(
    ./
    ../include
    ../utils/imgui
    ../utils/tools
    ../utils/frame
)

add_subdirectory(Robbie)

# add_subdirectory(MapEditor)

add_subdirectory(LifeGame)

add_subdirectory(Maze)

add_subdirectory(Some)

# [install]
install(FILES ModulesConfig.ini 
    DESTINATION ${CMAKE_INSTALL_PREFIX}/bin/
    PERMISSIONS OWNER_WRITE OWNER_READ GROUP_READ GROUP_WRITE WORLD_READ
)
# install(DIRECTORY BiulabWidget  
#     DESTINATION ${CMAKE_INSTALL_PREFIX}/BiulabWidget
#     FILES_MATCHING PATTERN "*.h" PATTERN "*.hh"
#     PERMISSIONS OWNER_WRITE OWNER_READ GROUP_READ GROUP_WRITE WORLD_READ
# )
