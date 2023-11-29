CXXFLAGS = -g -std=c++17 -Wall -Wextra
CXX      = g++
CC = gcc
RELEASEFLAGS = -O2 -std=c++17 
play: release
	./release

release: rshaderprog.o rrenderer.o rhandler.o rgame.o glad.o:
	${CXX} $(RELEASEFLAGS) -L./dependencies/lib -I./dependencies/headers -D_DEBUG $^ -o $@ -lGL -lglfw3

	${CXX} $(CXXFLAGS) -L./dependencies/lib -I./dependencies/headers -D_DEBUG $^ -o $@ -lGL -lglfw3

rgame.o: src/main.cpp
	${CXX} $(RELEASEFLAGS) -L./dependencies/lib -I./dependencies/headers -D_DEBUG $^ -c -o $@ -lGL -lglfw3

rhandler.o: src/lib/handler.cpp 
	${CXX} $(RELEASEFLAGS) -L./dependencies/lib -I./dependencies/headers -D_DEBUG $^ -c -o $@ -lGL -lglfw3

rrenderer.o: src/lib/renderer.cpp
	${CXX} $(RELEASEFLAGS) -L./dependencies/lib -I./dependencies/headers -D_DEBUG $^ -c -o $@ -lGL -lglfw3

rshaderprog.o: src/lib/shaderprog.cpp
	${CXX} $(RELEASEFLAGS) -L./dependencies/lib -I./dependencies/headers -D_DEBUG $^ -c -o $@ -lGL -lglfw3

game: shaderprog.o renderer.o handler.o game.o glad.o
	${CXX} $(CXXFLAGS) -L./dependencies/lib -I./dependencies/headers -D_DEBUG $^ -o $@ -lGL -lglfw3

game.o: src/main.cpp
	${CXX} $(CXXFLAGS) -L./dependencies/lib -I./dependencies/headers -D_DEBUG $^ -c -o $@ -lGL -lglfw3

handler.o: src/lib/handler.cpp 
	${CXX} $(CXXFLAGS) -L./dependencies/lib -I./dependencies/headers -D_DEBUG $^ -c -o $@ -lGL -lglfw3

renderer.o: src/lib/renderer.cpp
	${CXX} $(CXXFLAGS) -L./dependencies/lib -I./dependencies/headers -D_DEBUG $^ -c -o $@ -lGL -lglfw3

shaderprog.o: src/lib/shaderprog.cpp
	${CXX} $(CXXFLAGS) -L./dependencies/lib -I./dependencies/headers -D_DEBUG $^ -c -o $@ -lGL -lglfw3

glad.o: dependencies/src/glad.c
	${CC} -I./dependencies/headers $^ -c -o $@ -lGL
clean:
	rm -f *.o game