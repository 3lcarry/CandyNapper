.PHONY= clean

CC=g++
OPTIONS= -g 
DEBUG= #-D DEBUG
GL_LIB= -lX11 -lXi -lXmu -lglut -lGL -lGLU -lm
LIBDIR=lib
INCLUDEDIR=include
_OBJ= Vertice.o Arista.o Triangulo.o Delaunay.o Obstaculo.o EcRecta.o Nodo.o Grafo.o Pathfinding.o IPathfinding.o
OBJ = $(patsubst %,$(LIBDIR)/%,$(_OBJ))

main:    src/main_sin-proyecto.cpp $(OBJ)
	$(CC) $(OPTIONS) $(DEBUG) -I$(INCLUDEDIR) src/main_sin-proyecto.cpp $(OBJ) $(GL_LIB) -o main

$(LIBDIR)/%.o : $(LIBDIR)/%.cpp $(INCLUDEDIR)/%.h
	$(CC) $(OPTIONS) $(DEBUG) -c -I $(INCLUDEDIR) -o $@ $<

clean:
	rm -f $(OBJ)  
