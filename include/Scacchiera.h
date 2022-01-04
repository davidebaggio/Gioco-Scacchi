
#ifndef SCACCHIERA_H
#define SCACCHIERA_H

#include <iostream>
#include <fstream>
#include <cctype>

using namespace std;

//class Scacchiera;
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
	//Pedina();
	Pedina(int, int, bool, char); // pos x, pos y, colore(true bianco, false nero), lettera ref
	virtual ~Pedina() {}

	int getX() const { return x; }
	int getY() const { return y; }
	void setPos(int, int);
	bool getColor() const {return color;}
	void setColor(bool);
	void setName(const char &n);
	char getName() const {return name;}
	bool isFirstMove() { return firstMove; }

	//virtual bool move(int, int, Scacchiera &);
	virtual bool checkPos(int destX, int destY, Pedina* matrice [8][8]) =0;

	friend ostream &operator<<(ostream &os, const Pedina &);

	Pedina (const Pedina&) = delete;
	Pedina& operator = (const Pedina&) = delete;

};
//_________________________________ SCACCHIERA ______________________________

class Scacchiera
{
private:
	Pedina *matrice[8][8];

	bool KingsHaveValidPositions();

public:
	Scacchiera();
	~Scacchiera();

	bool checkBoundaries(int, int);		//deve essere void <------------------
	
	// Pedina **getMatrice() { return matrice; }
	
	Pedina *getPedina(int x, int y) const { return matrice[x][y]; }
	void setPedina(Pedina *);
	bool isEmpty(int x, int y) const { return matrice[x][y] == nullptr; }


	bool move(Pedina* p, int destX, int destY);

	bool isScacco();
	bool isScaccoMatto();
	bool isPatta();

};

ostream &operator<<(ostream &os, const Scacchiera &);

class InvalidIndex
{
};

class InvalidPosition
{
};


#endif