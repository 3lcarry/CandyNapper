#######################################################
# Setteamos la ruta donde generaremos los ejecutables #
#######################################################
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../)

#########################
# Ejecutables generados #
#########################

# Version completa CandyNapper
add_executable(CandyNapper main.cpp)

# Entregable hito 1
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../../entregables)
add_executable(entregable-hito1 entregable-hito1.cpp)

##############################
# Linkado de los ejecutables #
##############################
target_link_libraries(CandyNapper core)
target_link_libraries(entregable-hito1 core)