// ALL 2.cpp : Defines the entry point for the console application.
//


#include <iostream>
using namespace std;

//Health small - 10%
int healthincsmall() {
  int health = 10;
	health = health * 1.10;
	cout << health << endl;
}
//Health medium - 25%
int healthincmedium() {
  int health = 10;
	health = health * 1.25;
	cout << health << endl;
}
//Health large - 50%
int healthinclarge() {
  int health = 10;
	health = health * 1.5;
	cout << health << endl;
}

//Damage low - 10%
int damageinclow() {
  int damage = 10;
	damage = damage * 1.1;
	cout << damage << endl;
}
//Damage medium - 20%
int damageincmedium() {
  int damage = 10;
	damage = damage * 1.2;
	cout << damage << endl;
}
//Damage high - 30%
int damageinchigh() {
  int damage = 10;
	damage = damage * 1.3;
	cout << damage << endl;
}

//Armour bronze - 20 points
int armourbronze() {
  int armour = 0;
	armour = armour + 20;
	cout << armour << endl;
}
//Armour silver - 60 points
int armoursilver() {
  int armour = 0;
	armour = armour + 60;
	cout << armour << endl;
}
//Armour gold - 100 points
int armourgold() {
  int armour = 0;
	armour = armour + 100;
	cout << armour << endl;
}

//Speed increase 50% time - 10 sec
//int speedincshort(){
//  int speed
//}
//Speed increase 50% time - 20 sec
//Speed increase 50% time - 30 sec

//Level jump - 1 level
int leveljump() {
  int level = 0;
	level = level + 1;
	cout << level << endl;
}

//Max health upgrade - 15%
int maxhealthsmall() {
  int maxhealth = 100;
	maxhealth = maxhealth * 1.15;
	cout << maxhealth << endl;
}
//Max health upgrade - 30%
int maxhealthmedium() {
  int maxhealth = 100;
	maxhealth = maxhealth * 1.30;
	cout << maxhealth << endl;
}
//Max health upgrade - 45%
int maxhealthlarge() {
  int maxhealth = 100;
	maxhealth = maxhealth * 1.45;
	cout << maxhealth << endl;
}

//Damaged goods are 30% less than what they normally are
//Improved items are 30% more than what they normally are



int main(){
    
    sqlite::sqlite db( "dungeonCrawler.db" ); 
    auto cur = db.get_statement(); 
    cur->set_sql("SELECT armour FROM users WHERE ")
    
  healthincsmall();
  healthincmedium();
  healthinclarge();
  damageinclow();
  damageincmedium();
  damageinchigh();
  armourbronze();
  armoursilver();
  armourgold();
  leveljump();
  maxhealthsmall();
  maxhealthmedium();
  maxhealthlarge();
	
    
    
    
    return 0;
}

  