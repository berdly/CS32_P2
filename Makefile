CXXFLAGS = -g -std=c++17 -Wall -Wextra -Werror
CXX      = g++

game: handler.o game.o
	${CXX} $(CXXFLAGS) -L./dependencies/glew/bin $^ -o $@ -lGL -lGLEW -lglut

game.o: src/main.cpp
	${CXX} $(CXXFLAGS)  -L./dependencies/glew/bin -I./dependencies/headers $^ -c -o $@ -lGL -lGLEW -lglut

handler.o: src/lib/handler.cpp
	${CXX} $(CXXFLAGS) -L./dependencies/glew/bin -I./dependencies/headers $^ -c -o $@ -lGL -lGLEW -lglut

clean:
	rm -f *.o game
