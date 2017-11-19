#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "IMGUI::imgui" for configuration "Debug"
set_property(TARGET IMGUI::imgui APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(IMGUI::imgui PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "CXX"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/imguid.lib"
  )

list(APPEND _IMPORT_CHECK_TARGETS IMGUI::imgui )
list(APPEND _IMPORT_CHECK_FILES_FOR_IMGUI::imgui "${_IMPORT_PREFIX}/lib/imguid.lib" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
