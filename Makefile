game: setup.o game.cpp
	g++ game.cpp setup.o -w -lSDL2 -lSDL2_image -o play

game-alt: setup.o game-alt.cpp
	g++ game-alt.cpp setup.o -w -lSDL2 -lSDL2_image -o play

setup.o: setup.cpp
	g++ -c setup.cpp -w -lSDL2 -lSDL2_image
