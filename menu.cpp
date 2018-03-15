#include <iostream>
#include <string>
#include "libsqlite.hpp"
#include "shop.h"
#include "weaponset.h"
#include "global.h"
using namespace std;
int shop(){
    sqlite::sqlite db( "dungeonCrawler.db" );
        
    auto cur = db.get_statement();   
    cur->set_sql("SELECT gold FROM users WHERE idUser=?;");
    cur->prepare();
    cur->bind(1,globalUserID); //global user id is used to find the users id
    cur->step();
    int goldamount = cur->get_int(0);
    // open database
    bool checkMenu = false;
    while(true){
        bool checkItem = true;
        cout<<"*-----------------------------------*"<<endl;
        cout<<"|        Welcome to the Cave        |"<<endl;
        cout<<"*-----------------------------------*"<<endl;
        cout<<"*-----------------------------------*"<<endl;
        cout<<"| 1 - Weapons                       |"<<endl;
        cout<<"| 2 - Potions or Level jump         |"<<endl;
        cout<<"| 3 - Go Back                       |"<<endl;
        cout<<"*-----------------------------------*"<<endl;
        char item;
        cin>>item; 
            if(item =='1' || item=='2'){
                checkMenu = false;
                if (item=='1'){
                    Weapons var; //define the object to print all weapons and assign them to a user
                    var.idUser = 7; // dont forget to assign this to the globalvariable   HERE
                    var.printWeapons(db);  //antonio part of the code
                    bool checkgetWeapon = false;
                    while(checkgetWeapon != true){
                        int weaponChoice;
                        cin >> weaponChoice;
                        if (weaponChoice>0 && weaponChoice<5){
                            checkgetWeapon = true;
                            var.assignWeapon(weaponChoice, db);
                        } 
                        else{
                            cout<<"You should type a number between 1 and 4"<<endl;
                        }
                    }
                }
                else if (item=='2'){
                    if (goldamount>=10)
                    {
                        shopMain(); //anir part of the code
                    }
                    else
                    {
                        cout << "You can't afford anything" << endl;
                    }    
                    
                }  
            }
            if(item == '3'){
                checkMenu= false;
            }
        
        if(item=='3'){
            break;
        }
        
    }
    return 0;
}
int menu()
{
    bool checkMenu = false;
    while(checkMenu != true)
    {
        cout<<"*-------------------*"<<endl;
        cout<<"| 1- Start the game |"<<endl;
        cout<<"| 2- Shop           |"<<endl;
        cout<<"*-------------------*"<<endl;
        char menuChoice;
        cin>> menuChoice; 
        if (menuChoice=='1' || menuChoice =='2')
        {
            if (menuChoice == '2')
            {
                shop();
            }
            if (menuChoice == '1'){
                checkMenu = true;
                return 1;
            }
        }       
    }   
}