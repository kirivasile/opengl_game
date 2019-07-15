cmake_minimum_required(VERSION 3.0)

project(OpenGL_Space VERSION 3.0)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "CMake Targets")

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

include(MacroUtils)

FIND_DEPENDENCIES()

if(UNIX)
    set(CMAKE_INSTALL_RPATH "${DEPENDENCIES_ROOT}/lib")
endif()

if(WIN32)
    COPY_DEPENDENCIES(main)
endif(WIN32)

ADD_TASKS(main)