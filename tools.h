#ifndef TOOLS_H
#define TOOLS_H

#include <iostream>
#include <istream>
#include <iomanip>
#include <fstream>

using namespace std;

//void menu(); // DEPRECATED
void clear();
void printFile(char *fileName);
void fixTime(int &, int &);
bool error(istream &buffer);
void handle(istream &buffer);
void pause();

#endif
