cmake_minimum_required(VERSION 3.15)
project(state_machine)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(test1
        Error.cpp
        Error.h
        Globals.h
        State.h
        StateMachine.h
        test.cpp
)

add_executable(
        test2
        Error.cpp
        Error.h
        Globals.h
        State.h
        StateMachine.h
        test2.cpp
)
