cmake_minimum_required(VERSION 3.23)
project(3d-engine)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(lib)


add_executable(3d-engine
        lib/glad/glad.c
        src/main.cpp
)

include_directories(lib/glm)
include_directories(src/includes)

target_include_directories(3d-engine PRIVATE src lib)
target_link_libraries(3d-engine PRIVATE glfw ImGui)