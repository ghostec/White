cmake_minimum_required(VERSION 3.9.4)
project(White)

set(paho-mqtt3_DIR .)
set(paho-mqttpp3_DIR .)
find_package(paho-mqtt3 REQUIRED)
find_package(paho-mqttpp3 REQUIRED)

include_directories(${paho-mqtt3_INCLUDE_DIRS})
include_directories(${paho-mqttpp3_INCLUDE_DIRS})

add_executable(White main.cpp)
target_link_libraries(White ${paho-mqtt3_LIBRARY} ${paho-mqttpp3_LIBRARY})

set_property(TARGET White PROPERTY CXX_STANDARD 17)
