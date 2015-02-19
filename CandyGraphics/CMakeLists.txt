project(CandyGraphics)

add_definitions(-g)
add_definitions(-DCANDYGRAPHICSROOT="${CMAKE_CURRENT_SOURCE_DIR}/Resources/")

file(COPY Resources DESTINATION .)

#####################################
# INCLUDES y LIBS                   #
#####################################
set(INCDIRS 
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)
        
set(LIBDIRS
    ${CMAKE_CURRENT_BINARY_DIR}/lib
)

include_directories(${INCDIRS})
                    
link_directories(${LIBDIRS})

#####################################
# Integracion con DOXYGEN           #
#####################################
if(DOXYGEN_FOUND)
    add_custom_target(doc
    ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/doxyfile
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMENT "Generating API documentation with Doxygen" VERBATIM
    )
endif(DOXYGEN_FOUND)


#########################
# Compilacion de la libreria #
#########################
add_subdirectory(lib)
#add_subdirectory(test)

######################################
# Compilacion de utilidades/ejemplos #
######################################
add_subdirectory(src)