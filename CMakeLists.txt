cmake_minimum_required(VERSION 3.10)

project(game VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(SDL2 REQUIRED)
find_package(spdlog CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(Threads REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED) 
if (NOT GLEW_FOUND)
    message(FATAL_ERROR "GLEW not found. Install libglew-dev.")
endif()

include(FetchContent)
FetchContent_Declare(
    imgui
    GIT_REPOSITORY https://github.com/ocornut/imgui.git
    GIT_TAG docking
)
FetchContent_MakeAvailable(imgui)
set(IMGUI_SRC
    ${imgui_SOURCE_DIR}/imgui.cpp
    ${imgui_SOURCE_DIR}/imgui_draw.cpp
    ${imgui_SOURCE_DIR}/imgui_tables.cpp
    ${imgui_SOURCE_DIR}/imgui_widgets.cpp
    ${imgui_SOURCE_DIR}/imgui_demo.cpp
    ${imgui_SOURCE_DIR}/backends/imgui_impl_sdl2.cpp
    ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
)
add_library(imgui STATIC ${IMGUI_SRC})
target_include_directories(imgui PUBLIC
    ${imgui_SOURCE_DIR}
    ${imgui_SOURCE_DIR}/backends
    ${SDL2_INCLUDE_DIRS}
)
target_compile_definitions(imgui PUBLIC IMGUI_IMPL_OPENGL_LOADER_GLEW)
target_link_libraries(imgui PUBLIC
    ${SDL2_LIBRARIES}
    OpenGL::GL
    GLEW::GLEW
)

file(GLOB_RECURSE SRC_FILES src/*.cpp)

include_directories(src)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(${PROJECT_NAME} ${SRC_FILES})
target_link_libraries(${PROJECT_NAME} PRIVATE 
    SDL2::SDL2 
    SDL2::SDL2main 
    SDL2_image 
    spdlog::spdlog 
    glm::glm
    imgui
    Threads::Threads 
    dl
    OpenGL::GL
    GLEW::GLEW
)
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -pedantic)

# Copy resources
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