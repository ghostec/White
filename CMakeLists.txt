cmake_minimum_required(VERSION 3.9.4)
project(White)

include(thirdparty/websocketpp/build/lib/cmake/websocketpp/websocketpp-config.cmake)
find_package(websocketpp REQUIRED)

set(ASIO_INCLUDE_DIR thirdparty/asio/asio/include)

include_directories(${WEBSOCKETPP_INCLUDE_DIR})
include_directories(${ASIO_INCLUDE_DIR})

add_executable(White src/main.cpp)

target_compile_definitions(White PUBLIC ASIO_STANDALONE=TRUE)
set_property(TARGET White PROPERTY CXX_STANDARD 17)
