cmake_minimum_required(VERSION 3.12)
project(snake)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "/usr/share/SFML/cmake/Modules")

find_package(SFML 2.4.2 COMPONENTS graphics audio window system REQUIRED)

include_directories(.)

add_executable(snake
        AI.cpp
        AI.h
        control.cpp
        control.h
        game.cpp
        game.h
        gui.cpp
        gui.h
        human.cpp
        human.h
        key.h
        main.cpp
        tui.cpp
        tui.h
        ui.cpp
        ui.h)
target_link_libraries(snake sfml-graphics sfml-audio sfml-window sfml-system)