#include <iostream>
#include <string>
#include <stdlib.h>
#include <unistd.h> //for usleep stuff
#include "libsqlite.hpp"
#include "battleScenario.h"
#include "battles.h"
#include "global.h"
using namespace std;
int globalUserID;
battleScenario battle;
int waitAbit(int sec){
    usleep(sec * 1000000); //the parameter works in micro-seconds 
}
void increaseGold(int amount, sqlite::sqlite &db){
    auto curGold = db.get_statement();//create query
    curGold->set_sql("UPDATE users SET gold=gold+amount WHERE idUser=?");
    curGold->prepare();
    curGold->bind(1,globalUserID);
    curGold->step();
       
}
bool weaponExist(int weaponId){ //function to 
    sqlite::sqlite db("dungeonCrawler.db");//open database
    auto cur = db.get_statement();//create query
    cur->set_sql("SELECT duration FROM weapons_user WHERE (idUser=? AND idWeapon=?)");
    cur->prepare();
    cur->bind(1,globalUserID);
    cur->bind(2,weaponId);
    int step = cur->step();
    cout<<step<<endl;
    if(step){
        return true;
    }
    else{
        return false;
    } 
}


void Battles::printWeapons(){
    //function to print all the weapons the user has
    int counter = 2;
    sqlite::sqlite db( "dungeonCrawler.db" ); // open database
    auto cur = db.get_statement(); // create query
    //join query between weapon and weaponds_user
    cur->set_sql("SELECT w.idWeapon, w.type, w.damage, w.attack, wu.duration FROM weapon w, weapons_user wu  WHERE (idUser=? AND w.idWeapon = wu.idWeapon)"); 
    //0-id weapon . 1-type. 2-damage. 3-attack. 4-duration from weapons_user. 
    cur->prepare();
    cur->bind(1,globalUserID);
    cout<<"Your weapons:"<<endl;
    cout<<"0 = Punch"<<"   "<<"10"<<endl;
    while(cur->step()){
        int totalDamage = cur->get_int(2)*cur->get_int(3);
        //example output weapon(duration) attack%
        cout<<cur->get_int(0)<<" = "<<cur->get_text(1)<<"("<<cur->get_int(4)<<") "<<totalDamage<<"%"<<endl;
        counter = counter +1;
    }

}

void Battles::printMonsterStatus(int levelUser){
    sqlite::sqlite db( "dungeonCrawler.db" ); // open database
    auto cur_monster = db.get_statement(); // create query
    cur_monster->set_sql("SELECT * FROM monsters WHERE idMonster=?");
    //0-id monster(int) . 1-name(text) . 2-health(int) . 3-attack(int) . 4-counter attack(int)
    cur_monster->prepare();
    cur_monster->bind(1,idMonster);
    cur_monster->step();
    cout<<"Health("<<cur_monster->get_int(2)<<") "<<"Attack("<<cur_monster->get_int(3)+(3*levelUser)<<") Counter Attack("<<cur_monster->get_int(4)<<")"<<endl;
    cout<<"---------------------------------------------------------"<<endl;
}

//int Battles::setUserVariables(){
//    //function to set user status between turns
//    return 0;
//}
//
//int Battles::monsterAttack(){
//    return 0;
//}


int Battles::startBattle(){
    int attackW;
    int damageW;
	sqlite::sqlite db("dungeonCrawler.db");//open database
	auto cur = db.get_statement();//create query
    
    
    cout<<"Your opponent is getting ready..."<<endl;
    waitAbit(1);
    cout <<"."<<endl;
    waitAbit(1);
	cout<<"Let's get started!"<<endl;
    waitAbit(1);
	cout << "\033[2J";
	
    cur->set_sql("SELECT COUNT(idMonster) FROM monsters");//to get the number of monsters that exist
    cur->prepare();
    cur->step();
    int numOfMonsters = cur->get_int(0);
    srand(time(0));
    int idMonster = rand() % numOfMonsters + 1; //generate a number between 1-4
    
    auto cur2 = db.get_statement();
    cur2->set_sql("SELECT * FROM monsters WHERE idMonster=?"); 
    // 0-idOnster . 1-name . 2-health . 3-attack . 4-counterattack   
    cur2->prepare();
    cur2->bind(1,idMonster);
    cur2->step();
    cout<<"You will fight a: "<< cur2->get_text(1)<<endl;
    auto cur_battle = db.get_statement();//create query
    //query to load user and monster variables
    cur_battle->set_sql("SELECT u.maxHealth, u.armor, u.level, m.health, m.attack, m.counterAttack FROM users u, monsters m WHERE u.idUser==? AND m.idMonster=?");
    //0-user health . 1-user armor . 2-user level . 3-monster health . 4-monster attack . 5-monster counterattack  all int
    cur_battle->prepare();
    cur_battle->bind(1,globalUserID);  
    cur_battle->bind(2,idMonster);
    cur_battle->step();
    float user_health = cur_battle->get_int(0);
    float user_armor = cur_battle->get_int(1);
    int user_level = cur_battle->get_int(2);
    float monster_health = cur_battle->get_int(3);
    float monster_attack = cur_battle->get_int(4);
    int monster_counterattack = cur_battle->get_int(5);
    //loaded monster variables about random number
    Battles var;  // create the object
    var.idMonster = idMonster;
    bool checkgame = false;
    while(checkgame != true){
		if (idMonster==1)
			battle.warrior();
		else if (idMonster==2)
			battle.mage();
		else if (idMonster==3)
			battle.hunter();
		else if (idMonster==4)
			battle.dragQueen();
		cout << "                                " << endl;
        var.printMonsterStatus(user_level);//print the monster status
		cout << "                                " << endl;
        var.printWeapons(); //print all the weapons the user has
		cout << "                                " << endl;
        bool checkWeapon = false;
        while(checkWeapon != true){
            int weaponToUSe;
            cin >> weaponToUSe;
			cout << " " << endl;
			cout << " " << endl;
			cout << " " << endl;
			cout << " " << endl;
			cout << " " << endl;
			cout << " " << endl;
			cout << " " << endl;
			cout << " " << endl;
            if(weaponExist(weaponToUSe) || weaponToUSe==0){
                //-----user turn
                if (weaponToUSe > 0){ 
                    checkWeapon = true;
                    cur_battle = db.get_statement();//create query
                    //query to load the variables of the weapon that the user chose
                    cur_battle->set_sql("SELECT w.type, w.damage, w.attack, wu.duration FROM weapon w, weapons_user wu  WHERE (wu.idUser=? AND w.idWeapon =? AND wu.duration > 0 )");
                    //0-weapon type(text) . 1-weapon damage(int) . 2- weapon attack(int) . 3-weapon-user duration(int) 
                    cur_battle->prepare();
                    cur_battle->bind(1,globalUserID);
                    cur_battle->bind(2,weaponToUSe);
                    cur_battle->step();
                    attackW = cur_battle->get_int(2);
                    damageW = cur_battle->get_int(1);
                }else{
                    checkWeapon = true;
                    //when the user choose to punch
                    attackW = 50;
                    damageW = 1;
					cout << "\033[2J";
                }
            }
            
        }
        
        monster_health = monster_health - (attackW * damageW);//decrease the mosnter health multiplying the attack by damage
        if (monster_counterattack > 0){
            user_health = user_health - monster_counterattack;
        }
        //--------------
        //------monster turn
        cout<<"Enemy's turn"<<endl;
        float totalMonsterDamage = monster_attack * user_level;
        if (user_armor > 0){
            user_armor = user_armor-(0.25*totalMonsterDamage);
            user_health = user_health-(0.15*totalMonsterDamage);
        }else{
            user_health = user_health - totalMonsterDamage;
        }
        cout<<user_health<< "Your Health"<<endl;
        cout<<monster_health<<"Monster's Health"<<<endl;
        if(monster_health <= 0){
            cout<<"You won"<<endl;
            //increaseGold(40,db);
            checkgame = true;
           
        }
        if(user_health <= 0){
            cout<<"You lost"<<endl;
            //increaseGold(15,db);
            checkgame= true;
            
        }
    }
    return 0;
    
}
