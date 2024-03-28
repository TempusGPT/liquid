cmake_minimum_required(VERSION 3.28.3)
project(snake-game)

set(CMAKE_CXX_STANDARD 17)
set(CURSES_NEED_WIDE TRUE)

find_package(Curses)
include_directories(${CURSES_INCLUDE_DIR})
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
    liquid/src/lifecycle.cpp
    liquid/src/signal.cpp
    liquid/src/timer.cpp
)

target_link_libraries(build.out ${CURSES_LIBRARIES})
