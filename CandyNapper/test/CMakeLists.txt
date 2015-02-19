###################
# Tests generados #
###################

add_executable(prueba-comp prueba-compilacion.cpp)
add_executable(prueba-entitys prueba-entitys.cpp)
add_executable(prueba-inout prueba-inout.cpp)
add_executable(prueba-graficos prueba-graficos.cpp)
add_executable(prueba-parser prueba-parser.cpp)

############################
# Linkado                  #
############################

target_link_libraries(prueba-comp candy-napper)
target_link_libraries(prueba-entitys candy-napper)
target_link_libraries(prueba-inout candy-napper)
target_link_libraries(prueba-graficos candy-napper)
target_link_libraries(prueba-parser candy-napper)

