#include <iostream>
#include <Windows.h>
using namespace std;

bool running = true;
int x = 2; // sets player starting position
int y = 2; // sets player starting position

char map[12][13] =  //draws a small map with an array in order to test movement and collision etc
{
	"            ",
	" ########## ",
	" #        # ",
	" ###    # # ",
	" #  #  #  # ",
	" #  #  #  # ",
	" #  #  #  # ",
	" # #  #   # ",
	" #   #    # ",
	" #  #     # ",
	" #  ####### ",
	"            "

};

char main()
{
	while (running == true)
	{
		system("cls");
		for (int i = 0; i < 12; i++)
		{
			cout << map[i] << endl;
		}

		system("pause>nul");
		if (GetAsyncKeyState(VK_DOWN) || GetAsyncKeyState(0x53)) //0x53 is the S key
		{
			int y2 = y + 1;  //works by adding and subtracting from the x and y coordinates 
			if (map[y2][x] == ' ') {
				map[y][x] = ' ';
				y++;
				map[y][x] = 'x';
			}
		}

		if (GetAsyncKeyState(VK_UP) || GetAsyncKeyState(0x57))//0x57 is the W key
		{
			int y2 = y - 1;
			if (map[y2][x] == ' ') {
				map[y][x] = ' ';
				y--;
				map[y][x] = 'x';
			}
		}

		if (GetAsyncKeyState(VK_RIGHT) || GetAsyncKeyState(0x44)) //0x44 is the D key
		{
			int x2 = x + 1;
			if (map[y][x2] == ' ') {
				map[y][x] = ' ';
				x++;
				map[y][x] = 'x';
			}
		}

		if (GetAsyncKeyState(VK_LEFT) || GetAsyncKeyState(0x41)) //0x41 is the A key
		{
			int x2 = x - 1;
			if (map[y][x2] == ' ') {
				map[y][x] = ' ';
				x--;
				map[y][x] = 'x';
			}
		}
	}
}
