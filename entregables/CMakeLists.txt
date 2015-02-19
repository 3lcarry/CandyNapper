add_executable(cargadorModelos cargadorModelos.cpp)
target_link_libraries(cargadorModelos candy-graphics)


file(COPY ej1.3ds DESTINATION .)
file(COPY ej2.3ds DESTINATION .)
file(COPY ej3.3ds DESTINATION .)
file(COPY ej4.3ds DESTINATION .)
file(COPY t1.jpg DESTINATION .)
file(COPY t2.jpg DESTINATION .)
file(COPY explorador.jpg DESTINATION .)
file(COPY defaultboy.3ds DESTINATION .)

