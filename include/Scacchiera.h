
#ifndef SCACCHIERA_H
#define SCACCHIERA_H

#include <iostream>
#include <fstream>
#include <cctype>

using namespace std;

class Scacchiera;
//_________________________________ PEDINA ______________________________
class Pedina
{
private:
	int x;
	int y;
	bool color;
	char name;
	bool firstMove;

public:
	Pedina();
	Pedina(int, int, bool, char); // pos x, pos y, colore(true bianco, false nero), lettera ref
	//~Pedina();

	int getX() const { return x; }
	int getY() const { return y; }
	void setPos(int, int);
	bool getColor() const;
	void setColor(bool);
	void setName(const char &n);
	char getName() const;
	bool isFirstMove() { return firstMove; }

	virtual bool move(int, int, Scacchiera &);
	virtual bool checkPos(int, int, Scacchiera &);

	friend ostream &operator<<(ostream &os, const Pedina &);

	class InvalidPosition
	{
	};
};
//_________________________________ SCACCHIERA ______________________________

class Scacchiera
{
private:
	static Pedina *matrice[8][8];

public:
	Scacchiera();

	bool checkBoundaries(int, int);
	bool isEmpty(int x, int y) const { return matrice[x][y] == nullptr; }
	// Pedina **getMatrice() { return matrice; }
	Pedina *getPedina(int x, int y) const { return matrice[x][y]; }
	void setPedina(Pedina *);

	bool isScacco();
	bool isScaccoMatto();
	bool isPatta();

	class InvalidIndex
	{
	};
};

ostream &operator<<(ostream &os, const Scacchiera &);

#endif