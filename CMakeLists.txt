cmake_minimum_required(VERSION 3.15)
project(ECS-2)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

file(GLOB_RECURSE SOURCES src/*.cpp)
file(GLOB_RECURSE HEADERS headers/*.hpp)

# find_package(raylib CONFIG REQUIRED)
# include_directories("C:/vcpkg/installed/x64-windows/include")

# Dependencies
set(RAYLIB_VERSION 6.0)

include(FetchContent)
FetchContent_Declare(
    raylib
    DOWNLOAD_EXTRACT_TIMESTAMP OFF
    URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
)
FetchContent_MakeAvailable(raylib)

FetchContent_Declare(
  raygui
  GIT_REPOSITORY https://github.com/raysan5/raygui.git
  GIT_TAG        master
)
FetchContent_MakeAvailable(raygui)

include_directories(${CMAKE_SOURCE_DIR}/headers)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

target_link_libraries(${PROJECT_NAME} PRIVATE raylib)
target_include_directories(${PROJECT_NAME} PRIVATE ${raygui_SOURCE_DIR}/src)