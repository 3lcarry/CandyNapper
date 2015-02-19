# minimun required
cmake_minimum_required(VERSION 2.6)
	
PROJECT(CandyNapper)

#########################
# Flags para el proyecto#
#########################

# Flag para compilar la Box2D o usar la instalada. ON la compilara  
set(BOX2D ON)

# Flag para compilar los programas find_package(SFML)de test (DEBUG)
set(TEST_DEBUG ON)

##########################
# Deteccion de librerias #
##########################

# Deteccion (obligatoria) de OpenGL
find_package(OpenGL REQUIRED) 

find_package(Freetype REQUIRED)
message(${FREETYPE_INCLUDE_DIRS})
message(${FREETYPE_INCLUDE_DIRS})
# Deteccion de la SFML
find_package(SFML) #Seria recomendable saber la version

##############################################
# Compilación de librerías externas al juego #
##############################################

set(SFML_FOUND OFF) #¡¡¡COMENTAR!!!

# Compilacion de la FTGL (la ponemos la primera, por que creo que la SFML chafa algunas variables)
add_subdirectory(extlibs/FTGL)

# Compilación de la SFML (discrimina entre si esta instalada o no)
if(SFML_FOUND)
    set(SFML_HS ${SFML_INCLUDE_DIR})
    set(SFML_LIBS )
else(SFML_FOUND)
    add_subdirectory(extlibs/SFML)
    set(SFML_HS ${PROJECT_SOURCE_DIR}/extlibs/SFML/include)  
    set(SFML_LIBS ${PROJECT_BINARY_DIR}/extlibs/SFML)  
endif(SFML_FOUND)


# Compilacion de la Box2D (discrimina entre si esta instalada o no, segun el flag)
if(BOX2D)
    add_subdirectory(extlibs/Box2D)
endif(BOX2D)

# Compilacion de la tinyXML
add_subdirectory(extlibs/tinyXML)

# Compilacion de la poly2tri
add_subdirectory(extlibs/poly2tri)

# Compilacion de la Clipper
add_subdirectory(extlibs/Clipper)

#####################################
# INCLUDES y LIBS externos al juego #
#####################################

set(INCDIRS 
        #${PROJECT_SOURCE_DIR}/MotorIA/include
        ${SFML_HS}
        ${PROJECT_SOURCE_DIR}/extlibs/Box2D
        ${PROJECT_SOURCE_DIR}/extlibs/tinyXML
        ${PROJECT_SOURCE_DIR}/extlibs/FTGL
        ${PROJECT_SOURCE_DIR}/extlibs/poly2tri
        ${PROJECT_SOURCE_DIR}/extlibs/Clipper
        ${FREETYPE_INCLUDE_DIRS}
        ${PROJECT_SOURCE_DIR}/CandyMath/include
        ${PROJECT_SOURCE_DIR}/CandyGraphics/include
        ${PROJECT_SOURCE_DIR}/MotorIA/MaquinaEstados
        ${PROJECT_SOURCE_DIR}/MotorIA/Pathfinding/include
        ${PROJECT_SOURCE_DIR}/CandyMusic/include
        )
        
set(LIBDIRS
    #${PROJECT_BINARY_DIR}/MotorIA/lib
    ${SFML_LIBS}
    ${PROJECT_BINARY_DIR}/extlibs/Box2D/Box2D
    ${PROJECT_BINARY_DIR}/extlibs/tinyXML
    ${PROJECT_BINARY_DIR}/extlibs/FTGL
    ${PROJECT_BINARY_DIR}/extlibs/poly2tri
    ${PROJECT_BINARY_DIR}/extlibs/Clipper
    ${PROJECT_BINARY_DIR}/CandyMath/lib
    ${PROJECT_BINARY_DIR}/CandyGraphics/lib  
    ${PROJECT_BINARY_DIR}/MotorIA
    ${PROJECT_BINARY_DIR}/CandyMusic/lib
)

include_directories(${INCDIRS})
                    
link_directories(${LIBDIRS})

################################
# Compilacion de nuestras libs #
################################

add_definitions(-g -Wall)

#add_subdirectory(MotorIA/Pathfinding)
add_subdirectory(CandyMath)
add_subdirectory(CandyGraphics)
add_subdirectory(MotorIA)
add_subdirectory(CandyMusic)

##################################
# Compilacion de los ejecutables #
##################################
add_subdirectory(entregables)

#########################
# Compilacion del juego #
#########################
add_subdirectory(CandyNapper)

#########################
# Instalacion del juego #
######################### no funciona bien!!
 
install_files(${INCDIRS})
install_files(${LIBDIRS})

#ADD_EXECUTABLE(CandyNapper ${LIBDIRS})
#INSTALL(TARGETS CandyNapper DESTINATION candynapper)
#SET_TARGET_PROPERTIES(CandyNapper PROPERTIES LINKER_LANGUAGE C++)

SET(CPACK_GENERATOR "DEB")
SET(CPACK_DEBIAN_PACKAGE_MAINTAINER "JohnCor")
INCLUDE(CPack)
