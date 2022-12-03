cmake_minimum_required(VERSION 3.0.0)
project(PathFinderVisualizer VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 14)

if(MSVC)
else()
    add_compile_options(-g)
    add_compile_options(-Wfatal-errors)
endif()

add_compile_definitions(GLEW_STATIC)

include_directories(.)
include_directories(./inc)

include_directories(./deps/glfw/include)
include_directories(./deps/glew/include)
include_directories(./imgui)

link_directories(./deps/glfw/lib)
link_directories(./deps/glew/lib)

file(GLOB SOURCES
    ./*.hpp
    ./*.cpp
    ./inc/*.hpp
    ./inc/*.cpp
    ./deps/imgui/*.h
    ./deps/imgui/*.cpp)

add_executable(PathFinderVisualizer main.cpp ${SOURCES})

target_link_libraries(PathFinderVisualizer glew32 glfw3 OpenGL32)
