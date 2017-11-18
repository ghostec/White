cmake_minimum_required(VERSION 3.6.3)
project(White)

find_package(Pistache REQUIRED)

add_subdirectory(src)

add_executable(White src/main.cpp)
target_link_libraries(White pistache)
set_property(TARGET White PROPERTY CXX_STANDARD 17)
