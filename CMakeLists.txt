cmake_minimum_required(VERSION 3.0.0)
project(PathFinderVisualizer VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 14)

if(MSVC)
else()
    add_compile_options(-g)
    add_compile_options(-Wfatal-errors)
endif()

add_compile_definitions(GLEW_STATIC)

set(OpenGL_GL_PREFERENCE LEGACY)

include_directories(.)
include_directories(./alg)
include_directories(./inc)
include_directories(./deps/imgui)

if(UNIX)
    find_package(OpenGL REQUIRED)
    include_directories(./deps/unix/glfw_3.3.7)
    include_directories(./deps/unix/glew_2.1.0)
    link_directories(./deps/unix/glfw_3.3.7/lib)
    link_directories(./deps/unix/glew_2.1.0/lib)
else()
    include_directories(./deps/win/glfw/include)
    include_directories(./deps/win/glew/include)
    link_directories(./deps/win/glfw/lib)
    link_directories(./deps/win/glew/lib)
endif()

file(GLOB SOURCES
    ./*.hpp
    ./*.cpp
    ./inc/*.hpp
    ./inc/*.cpp
    ./alg/*.hpp
    ./alg/*.cpp
    ./deps/imgui/*.h
    ./deps/imgui/*.cpp)

add_executable(PathFinderVisualizer ${SOURCES})

if(UNIX)
    target_link_libraries(PathFinderVisualizer GLEW glfw3 ${OPENGL_LIBRARY})
else()
    target_link_libraries(PathFinderVisualizer glew32 glfw3 OpenGL32)
endif()
