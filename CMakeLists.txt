cmake_minimum_required(VERSION 3.23)
project(snake-game)

set(CMAKE_CXX_STANDARD 11)
set(CURSES_NEED_NCURSES TRUE)
set(CURSES_NEED_WIDE TRUE)

include_directories(liquid)
include_directories(src)

add_executable(
    build.out
    src/main.cpp
    liquid/src/app.cpp
    liquid/src/color.cpp
    liquid/src/component.cpp
    liquid/src/element.cpp
    liquid/src/format.cpp
    liquid/src/input.cpp
    liquid/src/lifecycle.cpp
    liquid/src/reactivity.cpp
    liquid/src/timer.cpp
)

find_package(Curses)
target_include_directories(build.out PUBLIC ${CURSES_INCLUDE_DIR})
target_link_libraries(build.out ${CURSES_LIBRARIES})