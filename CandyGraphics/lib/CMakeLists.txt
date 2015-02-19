file(GLOB CGRAPHICS_LIB_FILES "*.cpp")

#add_definitions(-D_DEBUG_)
add_definitions(-Wall -g)

#set(CGRAPHICS_LIB_FILES Transformation.cpp GraphicalTree.cpp Ventana.cpp)
add_library(candy-graphics ${CGRAPHICS_LIB_FILES})
target_link_libraries(candy-graphics ${OPENGL_LIBRARY} candy-math sfml-window sfml-graphics tiny-xml FTGL)