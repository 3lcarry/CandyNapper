####################################
# Compilacion de la lib matematica #
####################################

add_definitions(-D_DEBUG_)


file(GLOB MATH_FILES "*.cpp")
add_library(candy-math ${MATH_FILES})
target_link_libraries(candy-math Clipper)