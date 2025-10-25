cmake_minimum_required(VERSION 3.20.0)

project(ThirdParty)


add_subdirectory(glfw)
add_subdirectory(glad)
add_subdirectory(stb)


if(UNIX)
	add_compile_definitions(HAVE_UNISTD_H)
	add_compile_definitions(HAVE_FCNTL_H)
endif ()

