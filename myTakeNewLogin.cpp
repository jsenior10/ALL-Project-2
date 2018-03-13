#include <iostream>
#include <string>
#include "libsqlite.hpp"
#include "logTableFunction.h"
#include "md5.h" //file downloaded from  http://www.zedwood.com/article/cpp-md5-function and md5.cpp as well
#include "main.h"
#include "loginForm.h"

using namespace std;
int globalUserID; //.cpp definition of globalUserID
string haskMd5(string password){ //function to hash the password
    return md5(password);
}
class BuildUser{
    public:
        string username, password, type;
        int gold, armor;
        BuildUser(){};
        int setValues(string username, string password, int gold, int armor, string type){
            sqlite::sqlite db( "dungeonCrawler.db" ); // open database
            auto cur_regist = db.get_statement(); // create query
            cur_regist->set_sql("INSERT INTO users(username,password,type,level,gold,maxHealth,armor) VALUES (?,?,?,1,?,100,?);");
            cur_regist->prepare();
            cur_regist->bind(1, username);
            cur_regist->bind(2,password);
            cur_regist->bind(3,type);
            cur_regist->bind(4,gold);
            cur_regist->bind(5,armor);
            cur_regist->step();
            auto cur2 = db.get_statement();
            cur2->set_sql("SELECT idUser FROM users WHERE username=?");
            cur2->prepare();
            cur2->bind(1,username);
            cur2->step();
            int id2 = cur2->get_int(0);
            globalUserID = id2;
            insertLogTable(id2,"New user"); // function to insert data into log table
            //db.close();
            return 0;
        }
};

class Witch : public BuildUser{
    public:
        Witch()
        {
            armor = 0;
            gold = 120;
            type = "Witch";
        }
        //string username;
        //string passwordWitch;
        void set()
        {
            setValues(username, password, gold, armor, type);
        }
};

class Soldier: public BuildUser{
    public:
        Soldier()
        {
            armor = 100;
            gold=100;
            type="Soldier";
        }
        //string usernameSoldier;
        //string passwordSoldier;
        void set()
        {
            setValues(username, password, gold, armor, type);
        }
        
};
class Fighter: public BuildUser{
    public:
        Fighter()
        {
            armor = 0;
            gold = 100;
            type = "Fighter";
        }
        void set()
        {
            setValues(username, password, gold, armor, type);
        }
        //setValues(usernameFighter, passwordFighter, goldFighter, armorFighter ,typeFighter);
};
class Rogue: public BuildUser{
    public:
        Rogue()
        {
            armor = 0;
            gold = 100;
            type = "Rogue";
        }
        void set()
        {
            setValues(username, password, gold, armor, type);
        }
        
};  
bool loginForm::login(){
    string username;
    string password;
    bool checking = false;
    while(checking != true){ //the code will run untill the user type the correct passsword
        sqlite::sqlite db( "dungeonCrawler.db" ); // open database
        auto cur = db.get_statement(); // create query
        bool checkUsername = false;
        bool checkPass = false;
        while(checkUsername != true){
            cout << "Who are you ?" << endl;
            cin >> username;
            cur->set_sql("SELECT * FROM users WHERE username=? LIMIT 1"); //query
            cur->prepare(); // run query
            cur->bind(1, username); //fill the placeholders
            if(cur->step()){
                checkUsername = true;
            }
        }
        while(checkPass != true){
            cout << "Please type the magic word !" << endl;
            cin >> password;
            if (md5(password).compare(cur->get_text(2)) == 0){
                cout << "\ndone"<< endl;
                checkPass = true;
                checking = true;
                int id = cur->get_int(0); 
                //global variable here
                globalUserID = id;
                insertLogTable(id,"Log in");
            }else{
                cout<<"Wrong password !"<< endl;
            }
        }
    }
    return true;
}
bool loginForm::regist(){
    string username;
    string password = "";
    string password2 = "";
    bool check = true;
    try {
        sqlite::sqlite db( "dungeonCrawler.db" ); // open database
        cout<< "Type your character's name ?"<< endl;
        cin >> username;
        while (check){   //will run untill both passwords match 
            cout << "Set your magic word !" << endl; //receive the password and replace by *
            cin >> password;
            cout << "Type your magic word again !" << endl;   //receive the password2 and replace by *
            cin >> password2;
            if(password == password2){
                check = false;
                cout<<"which type of character do you prefer? "<<endl;
                cout<<"1-Witch"<<endl;
                cout<<"2-Soldier"<<endl;
                cout<<"3-Fighter"<<endl;
                cout<<"4-Rogue"<<endl;
                int characterChoice;
                bool checkCharacter = true;
                while(checkCharacter){
                    try{
                        cin>>characterChoice;
                        if(characterChoice > 0 && characterChoice < 5){
                            switch(characterChoice){
                                case 1:
                                    {Witch witch;
                                    witch.username = username;
                                    witch.password = haskMd5(password);
                                    witch.set();
                                    checkCharacter = false;
                                    break;}
                                case 2:
                                    {Soldier soldier;
                                    soldier.username = username;
                                    soldier.password = haskMd5(password);
                                    soldier.set();
                                    checkCharacter = false;
                                    break;}
                                case 3:
                                    {Fighter fighter;
                                    fighter.username = username;
                                    fighter.password = haskMd5(password);
                                    fighter.set();
                                    checkCharacter = false;
                                    break;}
                                case 4:
                                    {Rogue rogue;
                                    rogue.username = username;
                                    rogue.password = haskMd5(password);
                                    rogue.set();
                                    checkCharacter = false;
                                    break;}
                            }
                        }else{
                            cout<<"you should type a number between 1-4"<<endl;
                        }
                    }catch(runtime_error){
                        cout<<"you should type a number between 1-4"<<endl;
                    }
                }
                return true;
            }else{
                cout << "password doesn't match. " << endl;
            }
        }
    }catch (sqlite::exception e){
        std::cerr << e.what() << std::endl;
        return true;
    }
    return false; 
}
int main(){
    int choice;
    bool checking =false;
    while (checking != true){
        cout<<"*----------*"<<endl;
        cout<<"| 1-login  |"<< endl;
        cout<<"| 2-regist |"<< endl; 
        cout<<"*----------*"<<endl;
        cin >> choice;
        if (choice == 1){
            checking = true;
            loginForm variables;
            variables.login();
        }
        else if(choice == 2){
            checking = true;
            loginForm variables;
            variables.regist();
        }
        else{
            cout << "Please type an available choice" << endl;
            checking = false;
        }
    }
    return 0;
}
