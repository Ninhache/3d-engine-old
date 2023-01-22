cmake_minimum_required(VERSION 3.23)
project(3d-engine)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(lib)

add_executable(3d-engine
        lib/glad/glad.c
        lib/stb/stb.c
        src/main.cpp
        src/core/scene.cpp
        src/shader.cpp
        src/mesh.cpp
        src/texture.cpp
)

include_directories(lib/glm)
include_directories(lib/assimp)
include_directories(lib/stb)
include_directories(src/headers)


target_include_directories(3d-engine PRIVATE src lib)
target_link_libraries(3d-engine PRIVATE glfw ImGui)