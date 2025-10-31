project(game LANGUAGES CXX)

file(GLOB_RECURSE GAME_SRC
    CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/gameplay/*.cpp
)

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

add_executable(game src/main.cpp ${GAME_SRC})
target_link_libraries(game PRIVATE engine SDL2::SDL2 SDL2::SDL2main imgui)
target_include_directories(game PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

target_compile_options(game PRIVATE -Wall -Wextra -Wpedantic)

add_custom_command(TARGET game POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
  ${CMAKE_SOURCE_DIR}/res $<TARGET_FILE_DIR:game>/res
  COMMENT "Copying resources for game"
)
