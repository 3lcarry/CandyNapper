file(GLOB FILES_IA "*.cpp")

#set(CGRAPHICS_LIB_FILES Transformation.cpp GraphicalTree.cpp Ventana.cpp)
add_library(candy-ia ${FILES_IA})
target_link_libraries(candy-ia candy-graphics)