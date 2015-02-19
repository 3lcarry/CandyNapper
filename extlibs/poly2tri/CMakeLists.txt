# Poly2tri CMake build file
cmake_minimum_required(VERSION 2.6)
#project (POL)

set (POLY_src
	poly2tri/common/shapes.cc
        poly2tri/sweep/cdt.cc
        poly2tri/sweep/advancing_front.cc
        poly2tri/sweep/sweep_context.cc
        poly2tri/sweep/sweep.cc
)

#testbed/main.cc


set (POLY_headers_directoris
	${CMAKE_CURRENT_SOURCE_DIR}/poly2tri
	${CMAKE_CURRENT_SOURCE_DIR}/poly2tri/common
	${CMAKE_CURRENT_SOURCE_DIR}/poly2tri/sweep
)

add_definitions(-g)

include_directories(${POLY_headers_directoris})
add_library(poly2tri ${POLY_src})

