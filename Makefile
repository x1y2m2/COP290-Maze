game: setup.o game.cpp
	g++ game.cpp setup.o -w -lSDL2 -lSDL2_image -o play

game-alt: setup.o blue.o yellow.o game-alt.cpp
	g++ game-alt.cpp setup.o blue.o yellow.o -w -lpthread -lSDL2 -lSDL2_image -o play

setup.o: setup.cpp
	g++ -c setup.cpp -w -lSDL2 -lSDL2_image

blue.o: blue.cpp
	g++ -c blue.cpp

yellow.o: yellow.cpp
	g++ -c yellow.cpp
