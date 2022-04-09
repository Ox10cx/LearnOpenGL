cmake_minimum_required(VERSION 3.5)

project(OpenGL LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
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

include_directories(
    ${GLFW_PATH}/include
    ${GLEW_PATH}/include
    vendor/stb_image
    vendor/glm)

find_library(OpenGL_LIBRARY OpenGL )
find_library(Cocoa_LIBRARY Cocoa )
find_library(IOKit_LIBRARY IOKit )

add_executable(OpenGL
  ${head_list}
  ${src_list}
  ${stb_image_list}
  ${shader_list}
  ${texture_list}
)

target_link_libraries(OpenGL
    glfw3
    GLEW
    ${OpenGL_LIBRARY}
    ${Cocoa_LIBRARY}
    ${IOKit_LIBRARY})
