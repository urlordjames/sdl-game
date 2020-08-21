cmake_minimum_required(VERSION "3.7")

project("sdl-game")

# include SDL2
find_package(SDL2 REQUIRED)
include_directories(${PROJECT_NAME} ${SDL2_INCLUDE_DIRS})

include_directories(${PROJECT_NAME} src/entity)
add_subdirectory(src)
