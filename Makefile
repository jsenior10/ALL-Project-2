all:
	echo "Be more specific please"
please-work :
	g++ --std=c++14 main.cpp level.cpp display.cpp player.cpp utils.cpp chest.cpp -o please-work
battle :
	g++ --std=c++14 battles.cpp -lncurses -o battles.o -lsqlite3
battleScenario :
	g++ --std=c++14 -lncurses battleScenario.cpp -o battleScenario.o
