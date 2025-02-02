cmake_minimum_required(VERSION 3.28)

project(ScratchScript)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# GLFW #
option(BUILD_SHARED_LIBS "" OFF)
option(GLFW_BUILD_EXAMPLES "" OFF)
option(GLFW_BUILD_TESTS "" OFF)
option(GLFW_BUILD_DOCS "" OFF)
option(GLFW_INSTALL "" OFF)
add_subdirectory(deps/glfw)

# GLEW #
option(glew-cmake_BUILD_SHARED "" OFF)
option(glew-cmake_BUILD_STATIC "" ON)
option(ONLY_LIBS "" ON)
add_subdirectory(deps/glew)

# GLM #
add_subdirectory(deps/glm)

# JSON #
option(JSON_BuildTests "" OFF)
add_subdirectory(deps/json)

# IMGUI #
add_library(imgui STATIC
        deps/imgui/imgui.cpp
        deps/imgui/imgui_demo.cpp
        deps/imgui/imgui_draw.cpp
        deps/imgui/imgui_tables.cpp
        deps/imgui/imgui_widgets.cpp
        deps/imgui/misc/cpp/imgui_stdlib.cpp
        deps/imgui/backends/imgui_impl_glfw.cpp
        deps/imgui/backends/imgui_impl_opengl3.cpp
)
target_include_directories(imgui PUBLIC deps/imgui deps/imgui/misc/cpp)
target_link_libraries(imgui PUBLIC glfw)

# SCRATCH #
file(GLOB_RECURSE source src/**.cpp include/**.hpp)

add_executable(scratch ${source})
target_include_directories(scratch PRIVATE include)
target_link_libraries(scratch PRIVATE glfw libglew_static glm::glm nlohmann_json::nlohmann_json imgui)

install(TARGETS scratch)
install(DIRECTORY resources DESTINATION bin)
