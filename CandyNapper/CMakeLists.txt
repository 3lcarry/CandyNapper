########################
# Proyecto CandyNapper #
########################
project(CandyNapper)

###################################
# Opciones del compilador - Debug #
###################################
# Esto deberia manejarse mediante un flag (para activar o desactivar)
add_definitions(-g -Wall)

################
# Zona Doxygen #
################

find_package(Doxygen)

# Creacion del objetivo "doc"
if(DOXYGEN_FOUND)
    add_custom_target(doc
    ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/doxyfile
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMENT "Generating API documentation with Doxygen" VERBATIM
    )
endif(DOXYGEN_FOUND)


##############################
# INCLUDES y LIBS "globales" #
##############################

set(CMAKE_DIR_ACTUAL "${PROJECT_SOURCE_DIR}")

set(INCDIRS 
    ${CMAKE_DIR_ACTUAL}/include
    )        
                    
set(LIBDIRS 
    ${CMAKE_DIR_ACTUAL}/lib
    )                    

# Indicamos las carpetas del include
include_directories(${INCDIRS})

# Indicamos las carpetas de las lib
link_directories(${LIBDIRS})

##############################
# Compilacion de los modulos #
##############################
add_subdirectory(lib)

###########################
# Compilacion de los test #
###########################
if(TEST_DEBUG)
    add_subdirectory(test)
endif(TEST_DEBUG)

##############################################
# Compilacion del juego y de los entregables #
##############################################
#add_subdirectory(src)

########################################################
# Copia de la carpeta resources al directorio de build #
########################################################
file(COPY resources DESTINATION .)
file(COPY resources DESTINATION ../entregables)