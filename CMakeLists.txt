cmake_minimum_required(VERSION 3.21)
project(3d-engine)

get_filename_component(CURRENT_DIR ${CMAKE_CURRENT_LIST_FILE} DIRECTORY)

set(CMAKE_CXX_STANDARD 20)
set(ASSIMP_INCLUDE_DIR ${CURRENT_DIR}/dependency/assimp-5.2.5/include)
set(ASSIMP_LIBRARIES ${CURRENT_DIR}/dependency/assimp-5.2.5/bin/libassimp.so.5.2.5)

#set(CMAKE_BUILD_TYPE Debug)

add_subdirectory(include)

add_executable(3d-engine
        include/glad/glad.c
        include/stb/stb.c
        src/main.cpp
        src/scene.cpp
        src/shader.cpp
	src/model.cpp
        src/mesh.cpp
        src/texture.cpp
	src/camera.cpp
        src/cubemap.cpp
        src/meshes/light.cpp
        src/meshes/pointLight.cpp
        src/meshes/directionalLight.cpp
        src/gui/gui.cpp
        src/gui/userParametersGui.cpp
        src/postprocessing.cpp
        src/framebuffer.cpp
)


include_directories(include/glm)
include_directories(include/assimp)
include_directories(include/stb)
include_directories(src/headers)
include_directories(${ASSIMP_INCLUDE_DIRS})

target_include_directories(3d-engine PRIVATE src include)
target_link_libraries(3d-engine PRIVATE glfw ImGui ${ASSIMP_LIBRARIES})

