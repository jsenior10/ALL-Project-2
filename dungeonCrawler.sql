PRAGMA foreign_keys=OFF;
BEGIN TRANSACTION;
CREATE TABLE users(
idUser INTEGER PRIMARY KEY AUTOINCREMENT,
username TEXT NOT NULL,
password TEXT NOT NULL,
type text NOT NULL,
level INT DEFAULT 0,
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
INSERT INTO "logTable" VALUES(1,0,'Log in','2018-03-01 19:06:21');
INSERT INTO "logTable" VALUES(2,0,'Log in','2018-03-01 19:08:27');
INSERT INTO "logTable" VALUES(3,0,'New user','2018-03-01 19:15:04');
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
INSERT INTO "monsters" VALUES(1,'Warrior',80,60,10);
INSERT INTO "monsters" VALUES(2,'Mage',100,40,20);
INSERT INTO "monsters" VALUES(3,'Hunter',80,70,5);
INSERT INTO "monsters" VALUES(4,'Drag Queen',80,60,10);
CREATE TABLE weapons_user(
idWeapon INTEGER NOT NULL,
idUser INTEGER NOT NULL
, duration INTEGER DEFAULT 0);
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
DELETE FROM sqlite_sequence;
INSERT INTO "sqlite_sequence" VALUES('monsters',4);
INSERT INTO "sqlite_sequence" VALUES('logTable',3);
INSERT INTO "sqlite_sequence" VALUES('users',1);
INSERT INTO "sqlite_sequence" VALUES('puzzle',7);
COMMIT;
