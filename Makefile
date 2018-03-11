please-work :
g++ --std=c++14 main.cpp level.cpp display.cpp player.cpp utils.cpp chest.cpp entity.cpp enemy.cpp battles.cpp battleScenario.cpp puzzle.cpp intro.cpp -o please-work -lsqlite3
battles:
	g++ --std=c++14 battles.cpp -o battles.o -lsqlite3
battleScenario:
	g++ --std=c++14  battleScenario.cpp -o battleScenario.o
loginForm:
	g++ --std=c++14 loginForm.cpp md5.cpp -o HAS -lsqlite3 -o loginForm

