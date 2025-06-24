cmake_minimum_required(VERSION 3.15)
project(example
  LANGUAGES CXX
  VERSION 1.0
)


set(ASSETS_DIR "${CMAKE_SOURCE_DIR}/assets")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

file(COPY
    "${CMAKE_SOURCE_DIR}/assets/"
    DESTINATION "${CMAKE_BINARY_DIR}/data/"
)

add_subdirectory(libs)
add_subdirectory(src)
target_include_directories(GravitySimulator PRIVATE include)
