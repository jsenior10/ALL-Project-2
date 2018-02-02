#include <iostream>
#include <string>
//#include "libsqlite.hpp"
#include <ncurses.h>
using namespace std;
bool login(){
    //int rc;
    //rc = sqlite3_open("dungeonCrawler.db", &db);
    cout<< "em desenvolvimento"<<endl;
    return true;
    
    
}
bool regist(){
    
    string username;
    char ch;
    char ch2;
    string password = "";
    string password2 = "";
    bool check = true;
    
    //sqlite::sqlite db( "dungeonCrawler.db" ); // open database
    
    cout<< "type yout username"<< endl;
    cin >> username;
    while (check){   //will run untill both passwords match 
        
        cout << "type your password" << endl; //receive the password and replace by *
        cin >> password;
        
        cout << "repeat password " << endl;   //receive the password2 and replace by *
        cin >> password2;
        
        if(password == password2){
            cout<<"done"<<endl;
            check = false;
        }
    }
    //auto cur = db.get_statement(); // create query
    //cur->set_sql( "INSERT INTO users(username, password, gold) VALUES (username, password, 100);" );
    //cur->prepare(); // run query
    
    
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