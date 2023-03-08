cmake_minimum_required(VERSION 3.21)
project(3d-engine)

set(CMAKE_CXX_STANDARD 20)
set(ASSIMP_INCLUDE_DIR ~/assimp/include)
set(ASSIMP_LIBRARIES ~/assimp/bin/libassimp.so.5.2.5)

#set(CMAKE_BUILD_TYPE Debug)

add_subdirectory(lib)

add_executable(3d-engine
        lib/glad/glad.c
        lib/stb/stb.c
        src/main.cpp
        src/scene.cpp
        src/shader.cpp
	src/model.cpp
        src/mesh.cpp
        src/texture.cpp
	src/camera.cpp
        src/meshes/light.cpp
        src/meshes/pointLight.cpp
        src/meshes/directionalLight.cpp
        src/gui/gui.cpp
        src/gui/userParametersGui.cpp
)


include_directories(lib/glm)
include_directories(lib/assimp)
include_directories(lib/stb)
include_directories(src/headers)
include_directories(${ASSIMP_INCLUDE_DIRS})

target_include_directories(3d-engine PRIVATE src lib)
target_link_libraries(3d-engine PRIVATE glfw ImGui ${ASSIMP_LIBRARIES})

