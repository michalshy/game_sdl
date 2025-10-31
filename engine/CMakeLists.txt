project(engine LANGUAGES CXX)

# engine sources & headers
file(GLOB_RECURSE ENGINE_SRC RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} src/*.cpp)
file(GLOB_RECURSE ENGINE_HDR  RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} src/*.h)

add_library(engine STATIC ${ENGINE_SRC} ${ENGINE_HDR})

# Publish engine public headers
target_include_directories(engine
    PUBLIC
      $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
      $<INSTALL_INTERFACE:src>
      $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/vendor/entt/single_include>
)

target_link_libraries(engine
    PUBLIC
      SDL2::SDL2          # makes SDL2 include dirs & link flags propagate
      Threads::Threads
      OpenGL::GL
      GLEW::GLEW
      spdlog::spdlog
      glm::glm
)

target_compile_options(engine PRIVATE -Wall -Wextra -Wpedantic)
