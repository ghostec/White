cmake_minimum_required(VERSION 3.6.3)
project(White)

option(target "Which target to build" "worker")

if(target STREQUAL "worker")
  include(${CMAKE_CURRENT_SOURCE_DIR}/worker.cmake)
elseif(target STREQUAL "server")
  include(${CMAKE_CURRENT_SOURCE_DIR}/server.cmake)
endif()
