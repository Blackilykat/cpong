cmake_minimum_required(VERSION 3.2)

include(FetchContent)

FetchContent_Declare(
    raylib
    DOWNLOAD_EXTRACT_TIMESTAMP OFF
    URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
    FIND_PACKAGE_ARGS
)
FetchContent_MakeAvailable(raylib)

project(pong C)

add_executable(pong src/main.c)

target_link_libraries(pong raylib)
