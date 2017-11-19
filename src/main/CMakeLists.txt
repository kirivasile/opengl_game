cmake_minimum_required(VERSION 3.0)

set(SRC_FILES
    Main.cpp
    common/Application.cpp
    common/Camera.cpp
    common/Mesh.cpp
    common/ShaderProgram.cpp
    common/PerlinNoise.cpp

    common/Application.hpp
    common/Camera.hpp
    common/Mesh.hpp
    common/ShaderProgram.hpp
    common/PerlinNoise.h
)

include_directories(common)

MAKE_TASK(main "${SRC_FILES}")