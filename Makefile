CXXFLAGS = -g -std=c++17 -Wall -Wextra -Werror
CXX      = g++

game: shaderprog.o renderer.o handler.o game.o
	${CXX} $(CXXFLAGS)  $^ -o $@ -lGL -lfreeglut

game.o: src/main.cpp
	${CXX} $(CXXFLAGS)  $^ -c -o $@ -lGL -lfreeglut

handler.o: src/lib/handler.cpp
	${CXX} $(CXXFLAGS)  $^ -c -o $@ -lGL -lfreeglut

renderer.o: src/lib/renderer.cpp
	${CXX} $(CXXFLAGS)  $^ -c -o $@ -lGL-lfreeglut

shaderprog.o: src/lib/shaderprog.cpp
	${CXX} $(CXXFLAGS)  $^ -c -o $@ -lGL -lfreeglut

clean:
	rm -f *.o game
