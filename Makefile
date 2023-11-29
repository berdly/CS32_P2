CXXFLAGS = -g -std=c++17 -Wall -Wextra
CXX      = g++

game: handler.o game.o
	${CXX} $(CXXFLAGS) -L./dependencies/glew/bin $^ -o $@ -lpthread -lGL -lGLEW -lglut

game.o: src/main.cpp
	${CXX} $(CXXFLAGS)  -L./dependencies/glew/bin -I./dependencies/headers $^ -c -o $@ -lpthread -lGL -lGLEW -lglut

handler.o: src/lib/handler.cpp
	${CXX} $(CXXFLAGS) -L./dependencies/glew/bin -I./dependencies/headers $^ -c -o $@ -lpthread -lGL -lGLEW -lglut

clean:
	rm -f *.o game
