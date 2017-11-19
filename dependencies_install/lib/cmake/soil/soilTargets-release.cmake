#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "SOIL::soil" for configuration "Release"
set_property(TARGET SOIL::soil APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(SOIL::soil PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/soil.lib"
  )

list(APPEND _IMPORT_CHECK_TARGETS SOIL::soil )
list(APPEND _IMPORT_CHECK_FILES_FOR_SOIL::soil "${_IMPORT_PREFIX}/lib/soil.lib" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
