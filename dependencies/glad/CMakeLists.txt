# GLAD subproject
cmake_minimum_required(VERSION 3.20)
project(glad VERSION 4.6 LANGUAGES C)
add_library(glad STATIC
  src/glad.c
)
target_include_directories(glad PRIVATE
  include/
)
