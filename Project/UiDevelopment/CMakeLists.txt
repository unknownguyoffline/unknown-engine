
cmake_minimum_required(VERSION 3.20.0)

project(UiDevelopment)

file(GLOB sources ${PROJECT_SOURCE_DIR}/*.cpp)

add_executable(UiDevelopment ${sources})
target_link_libraries(UiDevelopment Engine)
