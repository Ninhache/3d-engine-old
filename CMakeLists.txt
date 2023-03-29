cmake_minimum_required(VERSION 3.21)
project(3d-engine)

get_filename_component(CURRENT_DIR ${CMAKE_CURRENT_LIST_FILE} DIRECTORY)
get_filename_component(PARENT_DIR ${CURRENT_DIR} DIRECTORY)

set(CMAKE_CXX_STANDARD 20)
set(ASSIMP_INCLUDE_DIR ${CURRENT_DIR}/dependency/assimp-5.2.5/include)
set(ASSIMP_LIBRARIES ${CURRENT_DIR}/dependency/assimp-5.2.5/bin/libassimp.so.5.2.4)

#set(CMAKE_BUILD_TYPE Debug)

add_subdirectory(include)

add_executable(3d-engine
        ${CURRENT_DIR}/include/glad/glad.c
        ${CURRENT_DIR}/include/stb/stb.c
        ${CURRENT_DIR}/src/main.cpp
        ${CURRENT_DIR}/src/scene.cpp
        ${CURRENT_DIR}/src/shader.cpp
	${CURRENT_DIR}/src/model.cpp
        ${CURRENT_DIR}/src/mesh.cpp
        ${CURRENT_DIR}/src/texture.cpp
	${CURRENT_DIR}/src/camera.cpp
        ${CURRENT_DIR}/src/cubemap.cpp
        ${CURRENT_DIR}/src/meshes/light.cpp
        ${CURRENT_DIR}/src/meshes/pointLight.cpp
        ${CURRENT_DIR}/src/meshes/directionalLight.cpp
        ${CURRENT_DIR}/src/gui/gui.cpp
        ${CURRENT_DIR}/src/gui/userParametersGui.cpp
        ${CURRENT_DIR}/src/postprocessing.cpp
        ${CURRENT_DIR}/src/framebuffer.cpp
)


include_directories(${CURRENT_DIR}/include/glm)
include_directories(${CURRENT_DIR}/include/assimp)
include_directories(${CURRENT_DIR}/include/stb)
include_directories(${CURRENT_DIR}/src/headers)
include_directories(${ASSIMP_INCLUDE_DIRS})

target_include_directories(3d-engine PRIVATE src include)
target_link_libraries(3d-engine PRIVATE glfw ImGui ${ASSIMP_LIBRARIES})

