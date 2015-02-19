########################
# Proyecto CandyMusic  #
########################
project(CandyMusic)

add_definitions(-g -Wall)
add_definitions(-DCANDYMUSICROOT="${CMAKE_CURRENT_SOURCE_DIR}/MusicResources/")

file(COPY MusicResources DESTINATION .)

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
# Compilacion del motor de música (todo)       #
################################################
add_subdirectory(lib)
add_subdirectory(src)
