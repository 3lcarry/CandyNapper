add_executable(prueba-candygraphics prueba_compilacion.cpp)
target_link_libraries(prueba-candygraphics candy-graphics)

add_executable(prueba-transf prueba-transf.cpp)
target_link_libraries(prueba-transf candy-graphics)

add_executable(prueba-render prueba-render.cpp)
target_link_libraries(prueba-render candy-graphics candy-math)

add_executable(prueba-consola prueba-consola.cpp)
target_link_libraries(prueba-consola candy-graphics)

add_executable(prueba-model prueba-model.cpp)
target_link_libraries(prueba-model candy-graphics)

add_executable(prueba-adry prueba-adry.cpp)
target_link_libraries(prueba-adry candy-graphics)

file(COPY caja.3ds DESTINATION .)
file(COPY madera.jpg DESTINATION .)
file(COPY metal.jpg DESTINATION .)
file(COPY AnarchySans.otf DESTINATION .)
file(COPY intuitive.ttf DESTINATION .)


