#ifndef SHOP_H
#define SHOP_H

#include <iostream>
#include "libsqlite.hpp"
using namespace std;

int golddecarmourbronze(sqlite::sqlite &db);
int armourbronze(sqlite::sqlite &db);
int golddecarmoursilver(sqlite::sqlite &db);
int armoursilver(sqlite::sqlite &db);
int golddecarmourgold(sqlite::sqlite &db);
int armourgold(sqlite::sqlite &db);
int golddecleveljump(sqlite::sqlite &db);
int leveljump(sqlite::sqlite &db);
int golddecdurationsmall(sqlite::sqlite &db);
int durincsmall(sqlite::sqlite &db);
int golddecdurationmedium(sqlite::sqlite &db);
int durincmedium(sqlite::sqlite &db);
int golddecdurationlarge(sqlite::sqlite &db);
int durinclarge(sqlite::sqlite &db);
int armourcall(sqlite::sqlite &db);
int goldamountcall(sqlite::sqlite &db);
int shopMain();

#endif