CXXFLAGS = -O0 -std=c++17 
CXX      = g++
CC = gcc

game: shaderprog.o renderer.o handler.o imagerenderer.o game.o glad.o
	${CXX} $(CXXFLAGS) -L./dependencies/lib -I./dependencies/headers $^ -o $@ -lGL -lglfw3

game.o: src/main.cpp
	${CXX} $(CXXFLAGS) -L./dependencies/lib -I./dependencies/headers $^ -c -o $@ -lGL -lglfw3

handler.o: src/lib/handler.cpp 
	${CXX} $(CXXFLAGS) -L./dependencies/lib -I./dependencies/headers $^ -c -o $@ -lGL -lglfw3

imagerenderer.o: src/lib/imagerenderer.cpp
	${CXX} $(CXXFLAGS) -L./dependencies/lib -I./dependencies/headers $^ -c -o $@ -lGL -lglfw3

renderer.o: src/lib/renderer.cpp
	${CXX} $(CXXFLAGS) -L./dependencies/lib -I./dependencies/headers $^ -c -o $@ -lGL -lglfw3

shaderprog.o: src/lib/shaderprog.cpp
	${CXX} $(CXXFLAGS) -L./dependencies/lib -I./dependencies/headers $^ -c -o $@ -lGL -lglfw3

glad.o: dependencies/src/glad.c
	${CC} -I./dependencies/headers $^ -c -o $@ -lGL
clean:
	rm -f *.o game
