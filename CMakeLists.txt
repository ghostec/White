cmake_minimum_required(VERSION 3.6.3)
project(White)

find_package(Pistache REQUIRED)

option(target "Which target to build" "worker")

if(target STREQUAL "worker")
  include(${CMAKE_CURRENT_SOURCE_DIR}/src/CMakeListsWorker.txt)
elseif(target STREQUAL "server")
  include(${CMAKE_CURRENT_SOURCE_DIR}/src/CMakeListsServer.txt)
endif()
