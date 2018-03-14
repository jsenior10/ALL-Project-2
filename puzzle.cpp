#include <iostream>
#include <vector>
#include <string>
#include "libsqlite.hpp"
#include "utils.h"
#include "puzzle.h"
#include <unistd.h>

int waitAbit(int sec)
{
    usleep(sec * 1000000); //the parameter works in micro-seconds 
}

Puzzle::Puzzle(int x, int y, int HP) 
{
    xPos = x;
    yPos = y;
    currentHealth = HP;
}

bool Puzzle::question()
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
    std::cout << "\033[2J" << std::endl;
    std::cout << Quest << std::endl;
    
    string userAnswer;
    std::cin >> userAnswer;
    
    string dbAnswer = cur->get_text(2);
    if(userAnswer == dbAnswer)
    {
		std::cout << "correct!" << std::endl;
		waitAbit(1);
        return true;
    }
    else
    {
		std::cout << "Incorrect!" << std::endl;
		waitAbit(1);
        return false;
    }
}

