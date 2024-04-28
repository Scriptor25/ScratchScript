file(GLOB_RECURSE src src/**.cpp include/**.hpp)

add_executable(ScratchScript ${src})
target_include_directories(ScratchScript PRIVATE include)
target_link_libraries(ScratchScript PRIVATE nlohmann_json::nlohmann_json)

install(TARGETS ScratchScript)
install(DIRECTORY resources DESTINATION bin)
