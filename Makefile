all:
<<<<<<< HEAD
	g++ --std=c++14 main.cpp level.cpp display.cpp player.cpp utils.cpp chest.cpp -o please-work
=======
	echo "Be more specific please"
please-work :
	g++ --std=c++14 main.cpp level.cpp display.cpp player.cpp utils.cpp chest.cpp -o please-work
battle :
	g++ --std=c++14 battles.cpp -o battles.o -lsqlite3
battleScenario :
	g++ --std=c++14  battleScenario.cpp -o battleScenario.o
login :
	g++ --std=c++14 loginForm.cpp md5.cpp -o HAS -lsqlite3 -o loginForm
>>>>>>> ace977152e25b106d952e0e08295f93aedb0e7f8
