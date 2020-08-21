add_executable(${PROJECT_NAME} main.cpp)

# link SDL2
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})
