cmake_minimum_required(VERSION 2.8)
project(QuadAssault)

include_directories(include)
link_directories(${CMAKE_SOURCE_DIR}/lib)
add_subdirectory(src)