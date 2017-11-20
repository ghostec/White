project(http)

set(
  http_src
  server.cpp
  worker.cpp
)

find_package(Pistache REQUIRED)

add_library(http ${http_src})
target_link_libraries(http pistache)
