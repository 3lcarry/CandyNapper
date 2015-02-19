#add_executable(demo-candygraphics demo-candygraphics.cpp)
#target_link_libraries(demo-candygraphics candy-graphics)

#add_executable(cargador-modelos cargador-modelos.cpp)
#target_link_libraries(cargador-modelos candy-graphics)

add_executable(3ds2Bin 3ds2Bin.cpp)
target_link_libraries(3ds2Bin candy-graphics)

#file(COPY caja.3ds DESTINATION .)
#file(COPY madera.jpg DESTINATION .)
#file(COPY metal.jpg DESTINATION .)
#file(COPY AnarchySans.otf DESTINATION .)
#file(COPY intuitive.ttf DESTINATION .)
#file(COPY monigote.3ds DESTINATION .)

