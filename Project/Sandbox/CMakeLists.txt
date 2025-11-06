cmake_minimum_required(VERSION 3.20.0)

project(Sandbox)

file(GLOB sources ${PROJECT_SOURCE_DIR}/*.cpp)

add_executable(Sandbox ${sources})
target_link_libraries(Sandbox Engine)
set_target_properties(Sandbox PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}")