CXXFLAGS = -g -std=c++17 -Wall -Wextra -Werror
CXX      = g++

game: shaderprog.o renderer.o handler.o game.o
	${CXX} $(CXXFLAGS)  $^ -o $@ -lGL -lglut

game.o: src/main.cpp
	${CXX} $(CXXFLAGS)  $^ -c -o $@ -lGL -lglut

handler.o: src/lib/handler.cpp
	${CXX} $(CXXFLAGS)  $^ -c -o $@ -lGL -lglut

clean:
	rm -f *.o game
