set(FILES_MS
            MaquinaEstados/State.cpp
            MaquinaEstados/StateMachine.cpp)
            
set(FILES_PF
            Pathfinding/lib/Grafo.cpp
            Pathfinding/lib/Nodo.cpp
            Pathfinding/lib/Pathfinding.cpp
	    	Pathfinding/lib/IPathfinding.cpp)
            
add_definitions(-Wall -g)   
         
add_library(candy-ia ${FILES_MS} ${FILES_PF})
target_link_libraries(candy-ia poly2tri candy-math candy-graphics) #El candy-graphics esta por la clase Timer

#compilamos tests
add_subdirectory(Pathfinding/src)

### PRUEBAS MIAS ###
#add_subdirectory(Pathfinding2)