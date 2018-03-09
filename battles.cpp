 #include <iostream>
#include <string>
#include <stdlib.h> 
#include "libsqlite.hpp"
#include "battleScenario.h"
#include <unistd.h> //for usleep stuff
using namespace std;
int waitAbit(int sec){
    usleep(sec * 1000000); //the parameter works in micro-seconds 
}
int globalUserID = 2;  //dont forget to remove the assign by 2
class Battles{
	
    public:
    int idUser;
    int idMonster;
    void printWeapons(){
        //function to print all the weapons the user has
        int counter = 2;
        sqlite::sqlite db( "dungeonCrawler.db" ); // open database
        auto cur = db.get_statement(); // create query
        //join query between weapon and weaponds_user
        cur->set_sql("SELECT w.idWeapon, w.type, w.damage, w.attack, wu.duration FROM weapon w, weapons_user wu  WHERE (idUser=? AND w.idWeapon = wu.idWeapon)"); 
        //0-id weapon . 1-type. 2-damage. 3-attack. 4-duration from weapons_user. 
        cur->prepare();
        cur->bind(1,idUser);
        cout<<"Your weapons:"<<endl;
        cout<<"0 = Punch"<<"   "<<"10"<<endl;
        while(cur->step()){
            int totalDamage = cur->get_int(2)*cur->get_int(3);
            //example output weapon(duration) attack%
            cout<<cur->get_int(0)<<"- "<<cur->get_text(1)<<"("<<cur->get_int(4)<<") "<<totalDamage<<"&"<<endl;
            counter = counter +1;
        }

    }
    void printMonsterStatus(int levelUser){
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
    int setUserVariables(){
        
        //function to set user status between turns
        
        return 0;
    }
    int monsterAttack(){
        return 0;
    }
};
bool weaponExist(int weaponId){
    sqlite::sqlite db("dungeonCrawler.db");//open database
    auto cur = db.get_statement();//create query
    cur->set_sql("SELECT duration FROM weapons_user WHERE idUser=? AND idWeapon=?");
    cur->prepare();
    cur->bind(1,globalUserID);
    cur->bind(2,weaponId);
    if(cur->step()==1){
        return true;
    }
    else{
        return false;
    }
    
}
int main(){
    int attackW;
    int damageW;
	sqlite::sqlite db("dungeonCrawler.db");//open database
	auto cur = db.get_statement();//create query
    auto cur2 = db.get_statement();
    
    cout<<"Your opponent is getting ready..."<<endl;
    waitAbit(1);
    cout <<"."<<endl;
    waitAbit(2);
	cout<<"Let's get started!"<<endl;
    waitAbit(1);
	cout << "\033[2J";
	
    cur->set_sql("SELECT COUNT(idMonster) FROM monsters");//to get the number of monsters that exist
    cur->prepare();
    cur->step();
    int numOfMonsters = cur->get_int(0);
    srand(time(0));
    int idMonster = rand() % numOfMonsters + 1; //generate a number between 1-4
    cur2->set_sql("SELECT * FROM monsters WHERE idMonster=?"); 
    // 0-idOnster . 1-name . 2-health . 3-attack . 4-counterattack   
    cur2->prepare();
    cur2->bind(1,idMonster);
    cur2->step();
    cout<<"You will fight a: "<< cur2->get_text(1)<<endl;
    bool stopGame = false;
	
    auto cur_battle = db.get_statement();//create query
    //query to load user and monster variables
    cur_battle->set_sql("SELECT u.maxHealth, u.armor, u.level, m.health, m.attack, m.counterAttack FROM users u, monsters m WHERE u.idUser==? AND m.idMonster=?");
    //0-user health . 1-user armor . 2-user level . 3-monster health . 4-monster attack . 5-monster counterattack  all int
    cur_battle->prepare();
    cur_battle->bind(1,globalUserID);  
    cur_battle->bind(2,idMonster);
    cur_battle->step();
    int user_health = cur_battle->get_int(0);
    int user_armor = cur_battle->get_int(1);
    int user_level = cur_battle->get_int(2);
    int monster_health = cur_battle->get_int(3);
    int monster_attack = cur_battle->get_int(4);
    int monster_counterattack = cur_battle->get_int(5);
    //load monster variables about random number
    cur = db.get_statement();//clean the one used before to create query
    Battles var;  // create the object
    var.idUser = globalUserID;            //CHANGEEEE, THIS VALUE IS ONLY FOr TESTING REASONS
    var.idMonster = idMonster;
	
    while(stopGame != true){
		
		if (idMonster==1)
			warrior();
		else if (idMonster==2)
			mage();
		else if (idMonster==3)
			hunter();
		else if (idMonster==4)
			dragQueen();
		
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
                    attackW = 10;
                    damageW = 1;
					cout << "\033[2J";
                }
            }
            
        }
        
        monster_health = monster_health - (attackW * damageW);//decrease the mosnter health multiplying the attack by damage
        if (monster_counterattack > 0){
            user_armor = user_armor - monster_counterattack;
        }
        //--------------
        //------monster turn
        cout<<"Enemy's turn"<<endl;
        int totalMonsterDamage = monster_attack * user_level;
        if (user_armor > 0){
            user_armor = user_armor-(0.75*totalMonsterDamage);
            user_health = user_armor-(0.25*totalMonsterDamage);
        }else{
            user_health =user_health - totalMonsterDamage;
        }
        cout<<user_health<<endl;
        cout<<monster_health<<endl;
        if(monster_health <= 0){
            cout<<"You won"<<endl;
            stopGame = true;
        }
        if(user_health <= 0){
            cout<<"You lost"<<endl;
            stopGame = true;
        }
    }

    return 0;
}