
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
link_directories(${CMAKE_CURRENT_BINARY_DIR}/lib)

add_subdirectory(lib)

add_executable(main src/main.cpp)
target_link_libraries(main candy-ia)

