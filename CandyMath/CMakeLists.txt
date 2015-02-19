########################
# Proyecto CandyMath   #
########################
project(CandyMath)

add_definitions(-g -Wall)

##############################################
# Indicamos los directorios de INCLUDE y LIB #
##############################################

set(INCDIRS 
    ${PROJECT_SOURCE_DIR}/include
    )        
                    
set(LIBDIRS 
    ${PROJECT_BINARY_DIR}/lib
    )                    

include_directories(${INCDIRS})
link_directories(${LIBDIRS})

################################################
# Compilacion de la libreria matematica (todo) #
################################################
add_subdirectory(lib)

########################
# Compilacion de tests #
########################
if(TEST_DEBUG)
    add_subdirectory(test)
endif(TEST_DEBUG)