cmake_minimum_required(VERSION 3.16)
set (CMAKE_CXX_STANDARD 20)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(JSON_BuildTests OFF CACHE INTERNAL "")
project(Fig)

find_package(spdlog CONFIG REQUIRED)
find_package(nlohmann_json 3.2.5 REQUIRED)

add_library(imgui)
file(GLOB_RECURSE IMGUI_SOURCE_FILES third/gui/imgui/*.cpp)
file(GLOB_RECURSE IMGUI_HEADER_FILES third/gui/imgui/*.h)
target_sources(imgui PRIVATE ${IMGUI_HEADER_FILES} ${IMGUI_SOURCE_FILES})

add_library(fig)
target_link_libraries(fig PRIVATE imgui spdlog::spdlog nlohmann_json::nlohmann_json GLEW)
target_include_directories(fig PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
file(GLOB_RECURSE SOURCE_FILES *.cpp events/*.cpp math/*.cpp mesh/*.cpp misc.*cpp)
file(GLOB_RECURSE HEADER_FILES *.h events/*.h math/*.h mesh/*.h misc.*h)

target_sources(fig PRIVATE ${HEADER_FILES} ${SOURCE_FILES})
