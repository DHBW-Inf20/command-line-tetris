command = 	g++ -std=c++17 -pthread
.ONESHELL:
tetris:
	$(command) -c ../*.cpp
	$(command) -c ../UI/*.cpp
	$(command) -c ../UI/DataClasses/*.cpp
	$(command) -c ../UI/DataClasses/Blocks/*.cpp
	$(command) -c ../Utilities/*.cpp
	$(command) -c ../GameLogic/Highscores/*.cpp
	$(command) -c ../GameLogic/*.cpp
	$(command) -c ../GameLogic/Input/*.cpp
	$(command) -o tetris  *.o
	rm *.o