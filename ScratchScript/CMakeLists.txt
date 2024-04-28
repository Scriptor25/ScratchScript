find_package(OpenGL REQUIRED)

file(GLOB_RECURSE src src/**.cpp include/**.hpp)

add_executable(ScratchScript ${src})
target_include_directories(ScratchScript PRIVATE include)
target_link_libraries(ScratchScript PRIVATE glfw libglew_static OpenGL::GL glm::glm nlohmann_json::nlohmann_json imgui imgui-glfw imgui-opengl3)

install(TARGETS ScratchScript)
install(DIRECTORY resources DESTINATION bin)

set_property(TARGET ScratchScript PROPERTY CXX_STANDARD 20)
