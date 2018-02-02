#include <iostream>
using namespace std;

int main()
{
    
    
    
    int mazeGeneration [4] [5] = 
    {
        {1,2,3,4,5},
        {2,3,4,5,6},
        {3,4,5,6,7},
        {4,5,6,7,8}
    };
    
    for ( int row = 0; row < 4; row++)
    {
        for (int column = 0; column < 5; column++)
        {
            cout << mazeGeneration[row][column] << " ";
        }
        cout << endl;
    }
}