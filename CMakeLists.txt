cmake_minimum_required(VERSION 3.28)

project(ScratchScript)

set_property(GLOBAL PROPERTY CXX_STANDARD 20)

set(GLFW_BUILD_DOCS OFF)
set(GLFW_INSTALL OFF)
set(GLFW_LIBRARY_TYPE STATIC)

set(glew-cmake_BUILD_SHARED OFF)
set(glew-cmake_BUILD_STATIC ON)
set(ONLY_LIBS ON)

set(IMGUI_STATIC_LIBRARY ON)
set(IMGUI_WITH_BACKEND ON)
set(IMGUI_BACKEND_PLATFORM GLFW)
set(IMGUI_BACKEND_OPENGL3 ON)

set(JSON_BuildTests OFF CACHE INTERNAL "")

add_subdirectory(GLEW)
add_subdirectory(GLFW)
add_subdirectory(ImGUI)
add_subdirectory(JSON)
add_subdirectory(ScratchScript)
