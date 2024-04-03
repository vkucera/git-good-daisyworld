cmake_minimum_required(VERSION 3.16)
project(daisyworld VERSION 0.1.0)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# require the use of C++17, without compiler-specific non-standard extension
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# abilita warning
string(APPEND CMAKE_CXX_FLAGS " -Wall -Wextra")

# enable the address sanitizer and the undefined-behaviour sanitizer in debug mode
string(APPEND CMAKE_CXX_FLAGS_DEBUG
       " -fsanitize=address,undefined -fno-omit-frame-pointer")
string(APPEND CMAKE_EXE_LINKER_FLAGS_DEBUG
       " -fsanitize=address,undefined -fno-omit-frame-pointer")

add_executable(daisyworld main.cpp daisy.cpp world.cpp)
