file(GLOB CPP_FILES "*.cpp")

add_definitions(-DCANDYROOT="${PROJECT_SOURCE_DIR}")

add_library(candy-napper ${CPP_FILES})
target_link_libraries(candy-napper candy-graphics candy-ia Box2D tiny-xml candy-music)
