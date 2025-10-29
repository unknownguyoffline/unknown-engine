cmake_minimum_required(VERSION 3.20.0)

#set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/libs)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/libs)

project(Engine)

message("${PROJECT_SOURCE_DIR}")
include_directories("${PROJECT_SOURCE_DIR}/Engine")
include_directories("${PROJECT_SOURCE_DIR}/Engine/ThirdParty/glm/")
include_directories("${PROJECT_SOURCE_DIR}/Engine/ThirdParty/assimp/include/")
include_directories("${PROJECT_SOURCE_DIR}/Engine/ThirdParty/imgui/")
include_directories("${PROJECT_SOURCE_DIR}/Engine/ThirdParty/entt/single_include")
include_directories("${PROJECT_SOURCE_DIR}/Engine/ThirdParty/glfw/include/")
include_directories("${PROJECT_SOURCE_DIR}/Engine/ThirdParty/freetype/include")
include_directories("${PROJECT_SOURCE_DIR}/Engine/ThirdParty/")

link_directories("${PROJECT_SOURCE_DIR}/Engine/ThirdParty/freetype/libs")

add_subdirectory(Engine)
add_subdirectory(Project)
