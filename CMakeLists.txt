cmake_minimum_required(VERSION 3.10)

project(game VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
find_package(SDL2 REQUIRED)
file(GLOB_RECURSE SRC_FILES src/*.cpp)
add_executable(${PROJECT_NAME} ${SRC_FILES})
target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2 SDL2::SDL2main)
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -pedantic)

set(RESOURCE_SOURCE_DIR "${CMAKE_SOURCE_DIR}/res")
set(RESOURCE_DEST_DIR "$<TARGET_FILE_DIR:game>/res")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_custom_command(
    TARGET game
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ARGS ${RESOURCE_SOURCE_DIR} ${RESOURCE_DEST_DIR}
    COMMENT "Copying resources directory 'res' to the executable output folder."
)