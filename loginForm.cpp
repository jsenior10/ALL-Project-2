#include <iostream>
#include <string>
#include "libsqlite.hpp"
using namespace std;
bool login(){
    string username;
    string password;
    try{
        sqlite::sqlite db( "dungeonCrawler.db" ); // open database
        
        auto cur = db.get_statement(); // create query
        cout << "Who are you ?" << endl;
        cin >> username;
        cout << "Please type the magic word !" << endl;
        cin >> password;
        cur->set_sql("SELECT * FROM users WHERE username=? AND password=? LIMIT 1");
        cur->prepare(); // run query
        cur->bind( 1, username );
        cur->bind( 2, password );
        if (cur->step()!= 0){
            cout << "done"<< endl;
        }
         
    }catch(sqlite::exception e){
        std::cerr << e.what() << std::endl;
        return true;
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

        cout<< "Who you wanna be ?"<< endl;
        cin >> username;
        while (check){   //will run untill both passwords match 

            cout << "Set your magic word !" << endl; //receive the password and replace by *
            cin >> password;

            cout << "Reset that !" << endl;   //receive the password2 and replace by *
            cin >> password2;

            if(password == password2){
                cout<<"done"<< username << password << endl;
                    
                check = false;
                auto cur = db.get_statement(); // create query
                cur->set_sql("INSERT INTO users(username,password,level,gold) VALUES (?,?,0,?);");
                cur->prepare(); // run query
                cur->bind( 1, username );
                cur->bind( 2, password );
                cur->bind()
                cur->step();
                return true;
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
    
    cout << "1-login"<< endl;
    cout << "2-regist" << endl;
    cin >> choice;
    if (choice == 1){
        login();
    }else{
        regist();
    }
    return 0;
}