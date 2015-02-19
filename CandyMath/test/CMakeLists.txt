########################
# Compilacion de tests #
########################
add_executable(test-matrix test-matrix.cpp)
target_link_libraries(test-matrix candy-math)

add_executable(test-mat4 test-mat4.cpp)
target_link_libraries(test-mat4 candy-math)

add_executable(test-rational test-rational.cpp)
target_link_libraries(test-rational candy-math)

add_executable(test-mcd test-mcd.cpp)
target_link_libraries(test-mcd candy-math)

add_executable(test-position test-position.cpp)
target_link_libraries(test-position candy-math)

add_executable(test-funcion test-funcion.cpp)
target_link_libraries(test-funcion candy-math)

add_executable(test-polygon test-polygon.cpp)
target_link_libraries(test-polygon candy-math candy-graphics)