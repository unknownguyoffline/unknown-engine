
cmake_minimum_required(VERSION 3.20.0)

project(UiDevelopment)

file(GLOB sources ${PROJECT_SOURCE_DIR}/*.cpp)

add_executable(UiDevelopment ${sources})
target_link_libraries(UiDevelopment Engine)
target_link_libraries(UiDevelopment z)
target_link_libraries(UiDevelopment bz2)
target_link_libraries(UiDevelopment brotlidec)
target_link_libraries(UiDevelopment png16)
target_link_libraries(UiDevelopment msdfgen-core)
target_link_libraries(UiDevelopment msdfgen-ext)
