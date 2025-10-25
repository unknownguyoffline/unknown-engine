cmake_minimum_required(VERSION 3.20.0)

project(ThirdParty)

set(FRETYPE_LIBRARY "${PROJECT_SOURCE_DIR}/freetype/libs/freetyped.lib")
set(FRETYPE_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}/freetype/include/")

#add_library(Freetype::Freetype UNKNOWN IMPORTED)
#set_target_properties(Freetype::Freetype PROPERTIES
#    IMPORTED_LOCATION "${FREETYPE_LIBRARY}"
#    INTERFACE_INCLUDE_DIRECTORIES "${FREETYPE_INCLUDE_DIRS}"
#)

add_subdirectory(glfw)
add_subdirectory(glad)
add_subdirectory(stb)
#add_subdirectory(msdf-atlas-gen)

if(UNIX)
	add_compile_definitions(HAVE_UNISTD_H)
	add_compile_definitions(HAVE_FCNTL_H)
endif ()

