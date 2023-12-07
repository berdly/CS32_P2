CXXFLAGS = -g -std=c++17 -Wall -Wextra
CXX      = g++
CC = gcc

game: shaderprog.o renderer.o handler.o game.o textrenderer.o glad.o
	${CXX} $(CXXFLAGS) -L./dependencies/lib -I./dependencies/headers -D_DEBUG $^ -o $@ -lGL -lglfw3 -lfreetype -lz

game.o: src/main.cpp
	${CXX} $(CXXFLAGS) -L./dependencies/lib -I./dependencies/headers -D_DEBUG $^ -c -o $@ -lGL -lglfw3 -lfreetype -lz

handler.o: src/lib/handler.cpp 
	${CXX} $(CXXFLAGS) -L./dependencies/lib -I./dependencies/headers -D_DEBUG $^ -c -o $@ -lGL -lglfw3 -lfreetype -lz
textrenderer.o: src/lib/textrenderer.cpp
	${CXX} $(CXXFLAGS) -L./dependencies/lib -I./dependencies/headers -D_DEBUG $^ -c -o $@ -lGL -lglfw3 -lfreetype -lz

renderer.o: src/lib/renderer.cpp
	${CXX} $(CXXFLAGS) -L./dependencies/lib -I./dependencies/headers -D_DEBUG $^ -c -o $@ -lGL -lglfw3 -lfreetype -lz

shaderprog.o: src/lib/shaderprog.cpp
	${CXX} $(CXXFLAGS) -L./dependencies/lib -I./dependencies/headers -D_DEBUG $^ -c -o $@ -lGL -lglfw3 -lfreetype -lz

glad.o: dependencies/src/glad.c
	${CC} -I./dependencies/headers $^ -c -o $@ -lGL
clean:
	rm -f *.o game
