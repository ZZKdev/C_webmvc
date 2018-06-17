include_directories(${PROJECT_SOURCE_DIR}/src/http/)
include_directories(${PROJECT_BINARY_DIR}/src/http/)

add_executable(test test.c)
target_link_libraries(test request)
