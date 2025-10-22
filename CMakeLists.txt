# Totally Random OpenGL Stuff (TROGS)
cmake_minimum_required(VERSION 3.20)

add_subdirectory(dependencies/glfw)
add_subdirectory(dependencies/glad)

project(TROGS VERSION 1.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(CXX_STANDARD_REQUIRED ON)
add_executable(TROGS
  src/main.cpp
  src/pch.cpp
)
target_include_directories(TROGS PRIVATE
  src/
  dependencies/glfw/include/
  dependencies/glad/include/
)
target_precompile_headers(TROGS PRIVATE
  src/pch.hpp
)
target_sources(TROGS PRIVATE
  src/pch.cpp
)

target_link_libraries(TROGS PRIVATE
  glfw
  glad
)
