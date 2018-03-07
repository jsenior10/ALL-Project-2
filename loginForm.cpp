#include <iostream>
#include <string>
#include "libsqlite.hpp"
#include "logTableFunction.h"
#include "md5.h" //file downloaded from  http://www.zedwood.com/article/cpp-md5-function and md5.cpp as well
using namespace std;
string haskMd5(string password){ //function to hash the password
    return md5(password);
}
class BuildUser{
    public:
        int setValues(string username,string password, int gold, int armor, string type){
            sqlite::sqlite db( "dungeonCrawler.db" ); // open database
            auto cur_regist = db.get_statement(); // create query
            cur_regist->set_sql("INSERT INTO users(username,password,level,gold,maxHealth,armor) VALUES (?,?,0,?,100,?);");
            cur_regist->prepare();
            cur_regist->bind(1, username);
            cur_regist->bind(2,password);
            cur_regist->bind(3,gold);
            cur_regist->bind(4,armor);
            cur_regist->step();
            auto cur2 = db.get_statement();
            cur2->set_sql("SELECT idUser FROM users WHERE username=?");
            cur2->prepare();
            cur2->bind(1,username);
            cur2->step();
            int id2 = cur2->get_int(0);
            insertLogTable(id2,"New user"); // function to insert data into log table
            return 0;
        }
};
class Witch: public BuildUser{
    public:
        string username;
        string password;
        int armor = 0;
        int gold = 120; 
        string type = "Witch";
        void setValues(string username,string password,int gold,int armor,string type)
        {
          BuildUser::setValues(username, password, gold, armor, type);
        }
        
};
class Soldier: public BuildUser{
    public:
        string username;
        string password;
        int armor = 100;
        int gold = 100;
        string type = "Soldier";
        void setValues(string username,string password,int gold,int armor,string type)
        {
          BuildUser::setValues(username, password, gold, armor, type);
        }
        
};
class Fighter: public BuildUser{
    public:
        string username;
        string password;
        int armor = 0;
        int gold = 100;
        string type = "Fighter";  
        void setValues(string username,string password,int gold,int armor,string type)
        {
          BuildUser::setValues(username, password, gold, armor, type);
        }
};
class Rogue: public BuildUser{
    public:
        string username;
        string password;
        int armor = 0;
        int gold = 100;
        string type = "Rogue";  
        void setValues(string username,string password,int gold,int armor,string type)
        {
          BuildUser::setValues(username, password, gold, armor, type);
        }
};  
bool login(){
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
            if (password.compare(cur->get_text(2)) == 0){
                cout << "\ndone"<< endl;
                checkPass = true;
                checking = true;
                int id = cur->get_int(0); 
                insertLogTable(id,"Log in");
            }else{
                cout<<"Wrong password !"<< endl;
            }
        }
    }
    return true;
}
bool regist(){
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
                                    Witch var;
                                    var.username = username;
                                    var.password = haskMd5(password);
                                    var.setValues();
                                    checkCharacter = false;
                                    break;
                                case 2:
                                    Soldier var;
                                    var.username = username;
                                    var.password = haskMd5(password);
                                    var.setValues();
                                    checkCharacter = false;
                                    break;
                                case 3:
                                    Fighter var;
                                    var.username = username;
                                    var.password = haskMd5(password);
                                    var.setValues();
                                    checkCharacter = false;
                                    break;
                                case 4:
                                    Rogue var;
                                    var.username = username;
                                    var.password = haskMd5(password);
                                    var.setValues();
                                    checkCharacter = false;
                                    break;
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
        cout << "1-login \n"<< endl;
        cout << "2-regist" << endl; 
        cin >> choice;
        if (choice == 1){
            checking = true;
            login();
        }
        else if(choice == 2){
            checking = true;
            regist();
        }
        else{
            cout << "Please type an available choice" << endl;
            checking = false;
        }
    }
    return 0;
}