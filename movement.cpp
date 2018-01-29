#include <iostream>
#include <Windows.h>
using namespace std;

bool running = true;
int playerX = 2; // sets player starting position
int playerY = 2; // sets player starting position

char map[12][13] =  //draws a small map with an array in order to test movement and collision etc
{
	"            ",
	" 1111111111 ",
	" 1        1 ",
	" 111 4  1 1 ",
	" 1  1 1   1 ",
	" 1  1  1  1 ",
	" 1  1  1  1 ",
	" 1 1  1   1 ",
	" 1   1    1 ",
	" 1  1     1 ",
	" 1  1111111 ",
	"            "

};

void main()
{
	while (running == true)
	{
		
		for (int i = 0; i < 12; i++)
		{
			cout << map[i] << endl;
		}

		system("pause>nul");
		if (GetAsyncKeyState(VK_DOWN) || GetAsyncKeyState(0x53)) //0x53 is the S key
		{
			system("cls");
			int playerY2 = playerY + 1;  //works by adding and subtracting from the x and y coordinates 
			if (map[playerY2][playerX] == ' ') {
				map[playerY][playerX] = ' ';
				playerY++;
				map[playerY][playerX] = 'x';
			}
			else if (map[playerY2][playerX] == '4') { // This checks what the next character is in the array in the direction of the button that was pressed
				map[playerY][playerX] = ' ';          // if the number below it is a 4, it runs the else if code, can be applied to other things
				map[playerY][playerX] = 'x';
				map[playerY2][playerX] = ' ';
				cout << "whip";
			}
		}

		if (GetAsyncKeyState(VK_UP) || GetAsyncKeyState(0x57))//0x57 is the W key
		{
			system("cls");
			int playerY2 = playerY - 1;
			if (map[playerY2][playerX] == ' ') {
				map[playerY][playerX] = ' ';
				playerY--;
				map[playerY][playerX] = 'x';
			}
		}

		if (GetAsyncKeyState(VK_RIGHT) || GetAsyncKeyState(0x44)) //0x44 is the D key
		{
			system("cls");
			int playerX2 = playerX + 1;
			if (map[playerY][playerX2] == ' ') {
				map[playerY][playerX] = ' ';
				playerX++;
				map[playerY][playerX] = 'x';
			}
		}

		if (GetAsyncKeyState(VK_LEFT) || GetAsyncKeyState(0x41)) //0x41 is the A key
		{
			system("cls");
			int playerX2 = playerX - 1;
			if (map[playerY][playerX2] == ' ') {
				map[playerY][playerX] = ' ';
				playerX--;
				map[playerY][playerX] = 'x';
			}
		}
	}
}
