cmake_minimum_required(VERSION 3.5)

project(OpenGL LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


add_definitions(-DGLEW_STATIC)

file(GLOB shader_list res/shaders/*.*)
file(GLOB texture_list res/textures/*.*)

set(GLFW_PATH dependency/GLFW)
link_directories(${GLFW_PATH}/lib-x86_64)

set(GLEW_PATH dependency/GLEW)
link_directories(${GLEW_PATH}/lib)


file(GLOB head_list *.h)
file(GLOB src_list *.cpp)
file(GLOB stb_image_list vendor/stb_image/*.*)
file(GLOB glm_head vendor/glm
    vendor/glm/detail
    vendor/glm/ext
    vendor/glm/gtc
    vendor/glm/gtx
    vendor/glm/simd)

file(GLOB imgui_src_list vendor/imgui/*.*)

file(GLOB test_list test/*.*)

include_directories(
    ${GLFW_PATH}/include
    ${GLEW_PATH}/include
    vendor/stb_image
    vendor/imgui
    test
    ${glm_head})

find_library(OpenGL_LIBRARY OpenGL )
find_library(Cocoa_LIBRARY Cocoa )
find_library(IOKit_LIBRARY IOKit )

add_executable(OpenGL
  ${head_list}
  ${src_list}
  ${test_list}
  ${stb_image_list}
  ${imgui_src_list}
  ${shader_list}
  ${texture_list}
)

target_link_libraries(OpenGL
    glfw3
    GLEW
    ${OpenGL_LIBRARY}
    ${Cocoa_LIBRARY}
    ${IOKit_LIBRARY})
