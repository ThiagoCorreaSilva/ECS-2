cmake_minimum_required(VERSION 3.15)
project(ECS-2)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

file(GLOB_RECURSE SOURCES src/*.cpp)
file(GLOB_RECURSE HEADERS headers/*.hpp)

find_package(raylib CONFIG REQUIRED)
include_directories("C:/vcpkg/installed/x64-windows/include")
include_directories(${CMAKE_SOURCE_DIR}/headers)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
target_link_libraries(${PROJECT_NAME} PRIVATE raylib)