#include <iostream>
#include <vector>
#include <string>
#include "utils.h"
#include "puzzle.h"

Puzzle::Puzzle(int x, int y, int HP) 
{
    xPos = x;
    yPos = y;
    currentHealth = HP;
}

string Puzzle::question()
{
    sqlite::sqlite db("dungeonCrawler.db");
    auto cur = db.get_statement();
    int numOfQuestions = 7;
    
    srand(time(0));
    int qNum = rand() % numOfQuestions + 1 ; //generate a number between 1-7 this decides the question you will recieve
    
    cur->set_sql("SELECT * FROM puzzle WHERE num=?");
    cur->prepare();
    cur->bind(1,qNum);
    cur->step();
    
    string Quest = cur->get_text(1);
    cout << Quest << endl;
    
    string userAnswer;
    cin >> userAnswer;
    
    string answer = cur->get_text(2);
    if(userAnswer == answer)
    {
        return true;
    }
    else
    {
        return false;
    }
}
