cmake_minimum_required(VERSION "3.7")

project("sdl-game")

find_package(SDL2 REQUIRED)
include_directories(${PROJECT_NAME} ${SDL2_INCLUDE_DIRS})

# static stuff
set(CMAKE_EXE_LINKER_FLAGS "-static")

add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})
