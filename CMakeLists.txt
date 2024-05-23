cmake_minimum_required(VERSION 3.12)

set(CMAKE_C_COMPILER "clang")
set(CMAKE_CXX_COMPILER "clang++")
set(CMAKE_CXX_STANDARD 17)

project(snake-game)
include_directories(liquid)
include_directories(src)
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS liquid/*.cpp src/*.cpp)
add_executable(build.out ${SOURCES})

if(APPLE)
    set(CMAKE_PREFIX_PATH /opt/homebrew/opt/ncurses)
endif()
set(CURSES_NEED_NCURSES TRUE)
set(CURSES_NEED_WIDE TRUE)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})
target_link_libraries(build.out ${CURSES_LIBRARIES})
