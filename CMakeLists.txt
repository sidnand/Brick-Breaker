cmake_minimum_required(VERSION 3.10)
project(BrickBreaker C)

# Set C standard
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Werror -Wno-unused-parameter")

# Find SDL2 package
find_package(SDL2 REQUIRED)

# Set source files
set(SOURCE_FILES main.c)

# Add executable
add_executable(BrickBreaker ${SOURCE_FILES})

# Link SDL2 to your executable
target_link_libraries(BrickBreaker SDL2::SDL2)