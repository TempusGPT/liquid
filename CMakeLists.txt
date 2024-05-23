cmake_minimum_required(VERSION 3.10)

set(CMAKE_C_COMPILER "clang")
set(CMAKE_CXX_COMPILER "clang++")
set(CMAKE_CXX_STANDARD 17)

project(snake-game)
include_directories(liquid)
include_directories(src)

add_executable(
    build.out
    src/main.cpp
    liquid/src/app.cpp
    liquid/src/color.cpp
    liquid/src/component.cpp
    liquid/src/effect.cpp
    liquid/src/element.cpp
    liquid/src/format.cpp
    liquid/src/input.cpp
    liquid/src/state.cpp
    liquid/src/timer.cpp
)

if(APPLE)
    set(CMAKE_PREFIX_PATH /opt/homebrew/opt/ncurses)
endif()
set(CURSES_NEED_NCURSES TRUE)
set(CURSES_NEED_WIDE TRUE)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})
target_link_libraries(build.out ${CURSES_LIBRARIES})
