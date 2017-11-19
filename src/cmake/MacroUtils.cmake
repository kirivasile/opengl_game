macro(FIND_DEPENDENCIES)
    option(USE_AUDO_DEPENDENCIES "Enable to use auto built dependencies" ON)
    set(DEPENDENCIES_ROOT CACHE PATH "Dependencies install path")
    if(USE_AUDO_DEPENDENCIES)
        if(DEPENDENCIES_ROOT)
            set(CMAKE_PREFIX_PATH ${DEPENDENCIES_ROOT})
            find_package(glew CONFIG)
            find_package(glfw3 CONFIG)
            find_package(glm CONFIG)
            find_package(assimp)
            find_package(soil CONFIG)
            find_package(imgui CONFIG)
        else()
            message("DEPENDENCIES_ROOT is not set")
        endif()
    else()
        find_package(glew CONFIG)
        find_package(glfw3 CONFIG)
        find_package(glm CONFIG)
        find_package(assimp)
        find_package(soil CONFIG)
        find_package(imgui CONFIG)
    endif()
endmacro(FIND_DEPENDENCIES)

macro(COPY_DEPENDENCIES DIRNAME)
    get_property(GLFW_LOCATION_DEBUG TARGET glfw PROPERTY IMPORTED_LOCATION_DEBUG)
    if(GLFW_LOCATION_DEBUG)
        install(FILES ${GLFW_LOCATION_DEBUG} DESTINATION ${CMAKE_INSTALL_PREFIX})
    else()
        message("GLFW_LOCATION_DEBUG is empty")
    endif()

    get_property(GLFW_LOCATION_RELEASE TARGET glfw PROPERTY IMPORTED_LOCATION_RELEASE)
    if(GLFW_LOCATION_RELEASE)
        install(FILES ${GLFW_LOCATION_RELEASE} DESTINATION ${CMAKE_INSTALL_PREFIX})
    else()
        message("GLFW_LOCATION_RELEASE is empty")
    endif()

    install(FILES ${DEPENDENCIES_ROOT}/bin/assimp-${ASSIMP_MSVC_VERSION}-mtd.dll DESTINATION ${CMAKE_INSTALL_PREFIX})
    install(FILES ${DEPENDENCIES_ROOT}/bin/assimp-${ASSIMP_MSVC_VERSION}-mt.dll DESTINATION ${CMAKE_INSTALL_PREFIX})
endmacro(COPY_DEPENDENCIES)

macro(ADD_TASKS DIRNAME)
	add_subdirectory("${DIRNAME}")
endmacro(ADD_TASKS DIRNAME)

macro(MAKE_TASK TRGTNAME SOURCEFILES)
    add_executable(${TRGTNAME} ${SOURCEFILES})

    target_include_directories(${TRGTNAME} PUBLIC
        ${ASSIMP_INCLUDE_DIR}
    )

    target_link_libraries(${TRGTNAME}
        GLEW::glew_s
        glm
        glfw
        SOIL::soil
        IMGUI::imgui
        ${ASSIMP_LIBRARY}
    )

    if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
        target_compile_options(${TRGTNAME} PRIVATE -std=c++11)
        target_link_libraries(${TRGTNAME} "-framework CoreFoundation")
    endif()

    if(CMAKE_COMPILER_IS_GNUCC)
        target_compile_options(${TRGTNAME} PUBLIC -std=c++11)
    endif()

    if(USE_CORE_PROFILE)
        target_compile_definitions(${TRGTNAME} PRIVATE USE_CORE_PROFILE)
    endif(USE_CORE_PROFILE)

    add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/${TRGTNAME}Data
            COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_CURRENT_SOURCE_DIR}/${TRGTNAME}Data ${CMAKE_CURRENT_BINARY_DIR}/${TRGTNAME}Data
            DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/${TRGTNAME}Data)

    add_custom_target(${TRGTNAME}_Data ALL
            DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/${TRGTNAME}Data)

    add_dependencies(${TRGTNAME} ${TRGTNAME}_Data)

    install(TARGETS ${TRGTNAME} RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX})
    install(DIRECTORY ${TRGTNAME}Data DESTINATION ${CMAKE_INSTALL_PREFIX})
endmacro(MAKE_TASK TRGTNAME SOURCEFILES)