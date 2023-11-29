CXXFLAGS = -g -std=c++17 -Wall -Wextra -Werror
CXX      = g++

game: handler.o game.o
	${CXX} $(CXXFLAGS) $^ -o $@ -lGL -lglew -lglut

game.o: src/main.cpp
	${CXX} $(CXXFLAGS)  -I./dependencies/headers $^ -c -o $@ -lGL -lglew -lglut

handler.o: src/lib/handler.cpp
	${CXX} $(CXXFLAGS) -I./dependencies/headers $^ -c -o $@ -lGL -lglew -lglut

clean:
	rm -f *.o game
