cmake_minimum_required(VERSION 3.20)
project(GRAPHICS101 C)

set(CMAKE_C_STANDARD 99)


add_definitions(-DGLEW_STATIC) #static linking flag for windows

find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)
add_executable(graphics main.c)

target_link_libraries(graphics GL GLEW glfw)

add_custom_command(
        TARGET graphics
        PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/resources/
        ${CMAKE_CURRENT_BINARY_DIR}/resources/
)