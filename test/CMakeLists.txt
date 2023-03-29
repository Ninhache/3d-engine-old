cmake_minimum_required(VERSION 3.21)
project(3d-engine-test)

get_filename_component(CURRENT_DIR ${CMAKE_CURRENT_LIST_FILE} DIRECTORY)
get_filename_component(PARENT_DIR ${CURRENT_DIR} DIRECTORY)

set(CMAKE_CXX_STANDARD 20)
set(ASSIMP_INCLUDE_DIR ${PARENT_DIR}/dependency/assimp-5.2.5/include)
set(ASSIMP_LIBRARIES ${PARENT_DIR}/dependency/assimp-5.2.5/bin/libassimp.so.5.2.4)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -g")

add_subdirectory(${PARENT_DIR}/include binarydir)

add_executable(3d-engine-test
        test.cpp
        ${PARENT_DIR}/include/glad/glad.c
        ${PARENT_DIR}/include/stb/stb.c
        ${PARENT_DIR}/src/shader.cpp
        ${PARENT_DIR}/src/model.cpp
        ${PARENT_DIR}/src/mesh.cpp
        ${PARENT_DIR}/src/texture.cpp
        ${PARENT_DIR}/src/camera.cpp
        ${PARENT_DIR}/src/cubemap.cpp
        ${PARENT_DIR}/src/meshes/light.cpp
        ${PARENT_DIR}/src/meshes/pointLight.cpp
        ${PARENT_DIR}/src/meshes/directionalLight.cpp
        ${PARENT_DIR}/src/postprocessing.cpp
        ${PARENT_DIR}/src/framebuffer.cpp
)


include_directories(${PARENT_DIR}/include/glm)
include_directories(${PARENT_DIR}/include/assimp)
include_directories(${PARENT_DIR}/include/stb)
include_directories(${PARENT_DIR}/src/headers)
include_directories(headers)
include_directories(${ASSIMP_INCLUDE_DIRS})


target_include_directories(3d-engine-test PRIVATE ${PARENT_DIR}/src ${PARENT_DIR}/include)
target_link_libraries(3d-engine-test PRIVATE glfw ${ASSIMP_LIBRARIES})