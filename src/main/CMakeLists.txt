cmake_minimum_required(VERSION 3.0)

set(SRC_FILES
    Main.cpp
    
    OpenGL/Application.cpp
    OpenGL/Camera.cpp
    OpenGL/Framebuffer.cpp
    OpenGL/Mesh.cpp
    OpenGL/ShaderProgram.cpp
    OpenGL/Texture.cpp
    SceneObjects/Billboard.cpp
    SceneObjects/Planet.cpp
    SceneObjects/Star.cpp
    SceneObjects/SkyBox.cpp
    Utils/MeshFactory.cpp
    
    OpenGL/Application.hpp
    OpenGL/Camera.hpp
    OpenGL/Framebuffer.hpp
    OpenGL/Mesh.hpp
    OpenGL/ScreenQuad.hpp
    OpenGL/ShaderProgram.hpp
    OpenGL/Texture.hpp
    SceneObjects/Billboard.h
    SceneObjects/Planet.h
    SceneObjects/Star.h
    SceneObjects/SkyBox.h
    SceneObjects/Base/SceneObject.hpp
    SceneObjects/Base/IRenderable.hpp
    SceneObjects/Base/IRotatable.hpp
    Utils/MeshFactory.h
)

include_directories(OpenGL)
include_directories(SceneObjects)
include_directories(SceneObjects/Base)
include_directories(Utils)

MAKE_TASK(main "${SRC_FILES}")