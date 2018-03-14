CC=g++ --std=c++14

all: game

display.o: display.cpp display.h
	$(CC) -c display.cpp 
	
level.o: level.cpp level.h
	$(CC) -c level.cpp

Login.o: Login.cpp loginForm.h
	$(CC) -c Login.cpp

md5.o: md5.cpp md5.h
	$(CC) -c md5.cpp

main.o: main.cpp
	$(CC) -c main.cpp

menu.o: menu.cpp
	$(CC) -c menu.cpp

player.o: player.cpp
	$(CC) -c player.cpp

utils.o: utils.cpp
	$(CC) -c utils.cpp

chest.o: chest.cpp chest.h
	$(CC) -c chest.cpp

entity.o: entity.cpp entity.h
	$(CC) -c entity.cpp

enemy.o: enemy.cpp enemy.h
	$(CC) -c enemy.cpp

battles.o: battles.cpp battles.h
	$(CC) -c battles.cpp

battleScenario.o: battleScenario.cpp battleScenario.h
	$(CC) -c battleScenario.cpp

puzzle.o: puzzle.cpp
	$(CC) -c puzzle.cpp

intro.o: intro.cpp intro.h
	$(CC) -c intro.cpp

weaponset.o: weaponset.cpp weaponset.h
	$(CC) -c weaponset.cpp

game: main.o level.o Login.o main.o md5.o menu.o player.o utils.o chest.o entity.o enemy.o battles.o battleScenario.o puzzle.o intro.o weaponset.o display.o
	$(CC) $^ -o $@ -lsqlite3
	
clean:
	rm *.o

