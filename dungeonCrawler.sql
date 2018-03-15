PRAGMA foreign_keys=OFF;
BEGIN TRANSACTION;
CREATE TABLE users(
idUser INTEGER PRIMARY KEY AUTOINCREMENT,
username TEXT NOT NULL,
password TEXT NOT NULL,
type text NOT NULL,
level INT DEFAULT 1,
gold INTEGER NOT NULL,
maxHealth INTEGER DEFAULT 100,
armor INTEGER NOT NULL
);
CREATE TABLE logTable(
idLog INTEGER PRIMARY KEY AUTOINCREMENT,
idUser INTEGER NOT NULL,
action text NOT NULL,
time TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

CREATE TABLE weapon(
idWeapon INTEGER PRIMARY KEY AUTOINCREMENT,
type TEXT NOT NULL,
damage INTEGER NOT NULL,
duration INTEGER NOT NULL, 
attack INTEGER DEFAULT 0,
price INTEGER NOT NULL
);
INSERT INTO "weapon" VALUES(1,'Shotgun',1.2,15,20,40);
INSERT INTO "weapon" VALUES(2,'Rifle',1.2,7,35,60);
INSERT INTO "weapon" VALUES(3,'Pistol',1.2,25,12,20);
INSERT INTO "weapon" VALUES(4,'sniper',1.2,1,50,100);
CREATE TABLE monsters(
idMonster INTEGER PRIMARY KEY AUTOINCREMENT,
name TEXT NOT NULL,
health INTEGER NOT NULL,
attack INTEGER NOT NULL,
counterAttack INTEGER NOT NULL
);
INSERT INTO "monsters" VALUES(1,'Warrior',80,30,10);
INSERT INTO "monsters" VALUES(2,'Mage',100,10,20);
INSERT INTO "monsters" VALUES(3,'Hunter',80,40,5);
INSERT INTO "monsters" VALUES(4,'Drag Queen',80,25,10);
CREATE TABLE weapons_user(
idWeapon INTEGER NOT NULL,
idUser INTEGER NOT NULL, 
duration INTEGER DEFAULT 0);
INSERT INTO "weapons_user" VALUES(2,1,6);
CREATE TABLE puzzle(
num integer primary key autoincrement,
question text not null,
answer text not null);
INSERT INTO "puzzle" VALUES(1,'what is 9^(3/2)','27');
INSERT INTO "puzzle" VALUES(2,'what continent is zimbabwae in?','africa');
INSERT INTO "puzzle" VALUES(3,'are you going to JJs tonight?!?','yes');
INSERT INTO "puzzle" VALUES(4,'is darts a sport?','no');
INSERT INTO "puzzle" VALUES(5,'differentiate: 3x^3 + 12x^2 + 7x','x^2 + 6x + 7');
INSERT INTO "puzzle" VALUES(6,'who is cooler, anir or angus?','angus');
INSERT INTO "puzzle" VALUES(7,'who said -if i can see further than others it is because i have been able to stand on the shoulders of giants-','isaac newton');
CREATE TABLE powerups(
idPowerUp INTEGER PRIMARY KEY AUTOINCREMENT,
name TEXT NOT NULL,
effectOnArmor INTEGER NOT NULL,
effectOnDamage INTEGER NOT NULL,
effectOnGold INTEGER NOT NULL);
CREATE TABLE powerups(
idPowerUp INTEGER PRIMARY KEY AUTOINCREMENT,
name TEXT NOT NULL,
effectOnHealth INTEGER NOT NULL,
effectOnGold INTEGER NOT NULL);
INSERT INTO "powerups" VALUES(1, "Small health upgrade", 5, 0);
insert into "powerups" values(2, "Health upgrade", 10, 0);
insert into "powerups" values(3, "20 Gold", 0, 20);
insert into "powerups" values(4, "40 Gold", 0, 40);
insert into "powerups" values(5, "70 Gold", 0, 70);
insert into "powerups" values(6, "100 Gold", 0, 100);
CREATE TABLE armourpotions(
IDPotion INTEGER PRIMARY KEY AUTOINCREMENT,
Price INTEGER NOT NULL,
Size TEXT NOT NULL,
Value INTEGER NOT NULL
);
INSERT INTO "armourpotions" VALUES(1,10,'small',40);
INSERT INTO "armourpotions" VALUES(2,15,'medium',70);
INSERT INTO "armourpotions" VALUES(3,20,'medium',150);
CREATE TABLE durationpotions(
IDPotion INTEGER PRIMARY KEY AUTOINCREMENT,
Price INTEGER NOT NULL,
Size TEXT NOT NULL,
Value INTEGER NOT NULL
);
INSERT INTO "durationpotions" VALUES(1,15,'small',3);
INSERT INTO "durationpotions" VALUES(2,25,'medium',6);
INSERT INTO "durationpotions" VALUES(3,65,'large',20);
DELETE FROM sqlite_sequence;
INSERT INTO "sqlite_sequence" VALUES('monsters',4);
INSERT INTO "sqlite_sequence" VALUES('users',1);
INSERT INTO "sqlite_sequence" VALUES('puzzle',7);
INSERT INTO "sqlite_sequence" VALUES('armourpotions',3);
INSERT INTO "sqlite_sequence" VALUES('durationpotions',3);
COMMIT;
