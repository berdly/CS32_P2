CXXFLAGS = -g -std=c++17 -Wall -Wextra
CXX      = g++

game: handler.o game.o
	${CXX} $(CXXFLAGS) -L./dependencies/glew/bin $^ -o $@ -lGL -lGLEW -lfreeglut

game.o: src/main.cpp
	${CXX} $(CXXFLAGS)  -L./dependencies/glew/bin -I./dependencies/headers $^ -c -o $@ -lGL -lGLEW -lfreeglut

handler.o: src/lib/handler.cpp
	${CXX} $(CXXFLAGS) -L./dependencies/glew/bin -I./dependencies/headers $^ -c -o $@ -lGL -lGLEW -lfreeglut

clean:
	rm -f *.o game
