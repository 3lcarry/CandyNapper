file(GLOB CMUSIC_LIB_FILES "*.cpp")

add_definitions(-Wall -g)

add_library(candy-music ${CMUSIC_LIB_FILES})
target_link_libraries(candy-music sfml-window sfml-graphics sfml-audio FTGL candy-math)