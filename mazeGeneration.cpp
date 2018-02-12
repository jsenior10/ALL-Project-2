#include <iostream>
#include <ctime>
using namespace std;

const int mazeSize = 31; //number can be changed to make some big sweaty mazes making it an even number makes it act a bit weird sometimes so its better to use an odd number
int blockedSquare = 1;
bool foundExit = false;
int maze[mazeSize][mazeSize] = {0};

void move(int m[mazeSize][mazeSize], int &r, int &c);
bool canMove(int m[mazeSize][mazeSize], int r, int c);
void solve(int m[mazeSize][mazeSize], int &r, int &c);
bool canSolve(int m[mazeSize][mazeSize], int r, int c);
void generateMaze(int m[mazeSize][mazeSize], int r, int c);
int findStart();
void printMaze(int m[mazeSize][mazeSize]);


int main()
{
    srand(time(0));

    for(int i = 0; i < mazeSize; ++i)
    for(int j = 0; j < mazeSize; ++j)
        maze[i][j] = 1;

    int r = findStart();
    //int r = 0;
    int c = 0;

    maze[r][c] = 0;

    generateMaze(maze, r, c);
    maze[r][c] = 2;
    printMaze(maze);
    std::cout << "Press enter to continue ..."; 
    std::cin.get(); 
     
    return 0; 
}

void generateMaze(int m[mazeSize][mazeSize], int r, int c)
{

    bool made = false;

    while(made == false)
    {
        if(c == mazeSize - 1)
            foundExit = true;


        if(canSolve(m, r, c))
        {
            solve(m, r, c);
        }
        else if(canMove(m, r, c))
        {
            m[r][c] = 2; //2 means you can't move from that square, setting any lower stops maze from being made
            move(m, r, c); //move to first open space that can be found
        }
        else
            made = true;

    }

    printMaze(m);
}


void move(int m[mazeSize][mazeSize], int &r, int &c)
{
    if(m[r][c+1] == 0)
        c++;
    else if(m[r+1][c] == 0)
        r++;
    else if(m[r][c-1] == 0)
        c--;
    else if(m[r-1][c] == 0)
        r--;
    else
        generateMaze(maze, r, c); //if maze cant be solved it generates a new one so the player doesnt have something that is impossible to solve

}

bool canMove(int m[mazeSize][mazeSize], int r, int c) //if there is an adjacent zero space, return true
{
    if(m[r][c+1] == 0)
        return true;
    else if(m[r+1][c] == 0)
        return true;
    else if(m[r][c-1] == 0)
        return true;
    else if(m[r-1][c] == 0)
        return true;
    else
        return false;
}

void solve(int m[mazeSize][mazeSize], int &r, int &c) //solves maze through with dijkstras algorithmto ensure it can be solved
{
    bool foundSolution = false;

    while(foundSolution == false)
    {

        int direction = (1 + rand() % 4) * 3;

        switch(direction)
        {
            case 3:
                if(c + 1 <= mazeSize - 1 && m[r][c + 2] == blockedSquare && m[r-1][c+1] == blockedSquare && m[r+1][c+1] == blockedSquare && m[r][c + 1] == blockedSquare)
                {
                    if(c == mazeSize - 2 && foundExit == true)
                        ; //do nothing
                    else
                    {
                        c++;
                        foundSolution = true;
                    }
                }
                break;
            case 6:
                if(r + 1 <= mazeSize - 2 && m[r + 2][c] == blockedSquare && m[r+1][c+1] == blockedSquare && m[r+1][c-1] == blockedSquare && m[r + 1][c] == blockedSquare && c != 0 && c != mazeSize - 1)
                {
                    r++;
                    foundSolution = true;
                }
                break;
            case 9:
                if(c - 1 >= 0 && m[r][c - 2] == blockedSquare && m[r-1][c-1] == blockedSquare && m[r+1][c-1] == blockedSquare && m[r][c - 1] == blockedSquare && c - 1 != 0)
                {
                    c--;
                    foundSolution = true;
                }
                break;
            case 12:
                if(r - 1 >= 1 && m[r - 2][c] == blockedSquare && m[r-1][c+1] == blockedSquare && m[r-1][c-1] == blockedSquare && m[r - 1][c] == blockedSquare && c != 0 && c != mazeSize - 1)
                {
                    r--;
                    foundSolution = true;
                }
                break;
        }
    }

    m[r][c] = 0;
}



bool canSolve(int m[mazeSize][mazeSize], int r, int c) //if an adjacent square can be moved to, return true
{
    bool solvable = false;

    if(r <= mazeSize - 3 && m[r + 2][c] == blockedSquare && m[r+1][c+1] == blockedSquare && m[r+1][c-1] == blockedSquare && m[r + 1][c] == blockedSquare && c != 0 && c != mazeSize - 1) //if adjacent space can be moved to 
    {
        solvable = true;
    }
    else if(c <= mazeSize - 2 && m[r][c + 2] == blockedSquare && m[r-1][c+1] == blockedSquare && m[r+1][c+1] == blockedSquare && m[r][c + 1] == blockedSquare)
    {
        if(c == mazeSize - 2 && foundExit == true)
            ; //do nothing
        else
        {
            solvable = true;
        }
    }
    else if(r >= 2 && m[r - 2][c] == blockedSquare && m[r - 1][c + 1] == blockedSquare && m[r-1][c-1] == blockedSquare && m[r - 1][c] == blockedSquare && c != 0 && c != mazeSize - 1) //if not on extreme left or right
    {
        solvable = true;
    }
    else if(c >= 1 && m[r][c - 2] == blockedSquare && m[r-1][c-1] == blockedSquare && m[r+1][c-1] == blockedSquare && m[r][c - 1] == blockedSquare && c - 1 != 0)
    {
        solvable = true;
    }

    return solvable;
}

int findStart()
{
    return 1 + rand() % (mazeSize - 2);
}

void printMaze(int m[mazeSize][mazeSize])
{

    cout << endl;

    for(int i = 0; i < mazeSize; ++i){
    for(int j = 0; j < mazeSize; ++j)
    {
        switch(m[i][j])
        {
            case 0:
                cout << "  ";
                break;
            case 1:
                cout << "▓▓";
                break;
            case 2:
                cout << "  ";
                break;
          case 3:
            cout << "  ";
            break;
        }
    }
    cout << endl;
    }
}
