cmake_minimum_required(VERSION 3.20.0)

project(ThirdParty)

set(FRETYPE_LIBRARY "${PROJECT_SOURCE_DIR}/freetype/libs/freetyped.lib")
set(FRETYPE_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}/freetype/include/")

set(MSDFGEN_USE_VCPKG OFF)
set(MSDFGEN_USE_SKIA OFF)
set(MSDFGEN_USE_TINYXML2 OFF)
set(MSDFGEN_DISABLE_SVG ON)
set(MSDFGEN_BUILD_STANDALONE OFF)
add_subdirectory(glfw)
add_subdirectory(glad)
add_subdirectory(stb)
add_subdirectory(msdfgen)

if(UNIX)
	add_compile_definitions(HAVE_UNISTD_H)
	add_compile_definitions(HAVE_FCNTL_H)
endif ()

