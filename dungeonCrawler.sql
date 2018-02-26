PRAGMA foreign_keys=OFF;
BEGIN TRANSACTION;
CREATE TABLE users(
idUser INTEGER PRIMARY KEY AUTOINCREMENT,
username TEXT NOT NULL,
password TEXT NOT NULL,
level INT DEFAULT 0,
gold INTEGER NOT NULL
);
CREATE TABLE logTable(
idLog INTEGER PRIMARY KEY AUTOINCREMENT,

idUser INTEGER NOT NULL,
action text NOT NULL,
time TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);
CREATE TABLE features (
idFeature INTEGER PRIMARY KEY AUTOINCREMENT,
idUser INTEGER NOT NULL,
maxHealth INTEGER DEFAULT 100,
armor INTEGER DEFAULT 0,
damage INTEGER NOT NULL
);
CREATE TABLE weapon (
idWeapon INTEGER PRIMARY KEY AUTOINCREMENT,
idUser INTEGER NOT NULL,
type TEXT NOT NULL,
damage INTEGER NOT NULL);
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
DELETE FROM sqlite_sequence;
INSERT INTO "sqlite_sequence" VALUES('users',4);
INSERT INTO "sqlite_sequence" VALUES('monsters',4);
COMMIT;
