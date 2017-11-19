add_subdirectory(src/http)

add_executable(White src/server.cpp)
target_link_libraries(White http)
set_property(TARGET White PROPERTY CXX_STANDARD 17)
