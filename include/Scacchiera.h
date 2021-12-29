
#ifndef SCACCHIERA_H
#define SCACCHIERA_H

#include <iostream>
#include <fstream>
#include <cctype>
using namespace std;

//_________________________________ SCACCHIERA ______________________________
class Scacchiera
{
private:
	Pedina matrice[8][8];

public:
	Scacchiera();

	bool checkBoundaries(int, int);
	bool isEmpty(int x, int y) const { return matrice[x][y].getName() == 'e'; }
	Pedina getPedina(int x, int y) const { return matrice[x][y]; }
	void setPedina(Pedina p);

	bool isScacco();
	bool isScaccoMatto();
	bool isPatta();

	class InvalidIndex
	{
	};
};

ostream &operator<<(ostream &os, const Scacchiera &);

#endif