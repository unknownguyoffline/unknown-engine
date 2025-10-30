
cmake_minimum_required(VERSION 3.20.0)

project(UiDevelopment)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}")

file(GLOB sources ${PROJECT_SOURCE_DIR}/*.cpp)

add_executable(UiDevelopment ${sources})
target_link_libraries(UiDevelopment Engine)
target_link_libraries(UiDevelopment freetype)
target_link_libraries(UiDevelopment msdfgen-core)
target_link_libraries(UiDevelopment msdfgen-ext)
