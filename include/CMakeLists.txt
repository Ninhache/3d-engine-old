include(FetchContent)

option(GLFW_BUILD_TESTS "" OFF)
option(GLFW_BUILD_DOCS "" OFF)
option(GLFW_INSTALL "" OFF)
option(GLFW_BUILD_EXAMPLES "" OFF)

FetchContent_Declare(
        glfw
        GIT_REPOSITORY https://github.com/glfw/glfw.git
        GIT_TAG  3.3.8
)

FetchContent_Declare(
        glm
        GIT_REPOSITORY https://github.com/g-truc/glm
        GIT_TAG 0.9.9.8
)

FetchContent_MakeAvailable(glfw glm)

# ImGui doesn't provide it's own CMakeLists, so we create it ourselves
file(GLOB_RECURSE imgui_src
        "imgui/*.h"
        "imgui/*.cpp"
)

add_library(ImGui ${imgui_src})

target_include_directories(ImGui PUBLIC imgui)
target_link_libraries(ImGui PUBLIC glfw)
