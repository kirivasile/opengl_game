#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "SOIL::soil" for configuration "Debug"
set_property(TARGET SOIL::soil APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(SOIL::soil PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "CXX"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/soild.lib"
  )

list(APPEND _IMPORT_CHECK_TARGETS SOIL::soil )
list(APPEND _IMPORT_CHECK_FILES_FOR_SOIL::soil "${_IMPORT_PREFIX}/lib/soild.lib" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
