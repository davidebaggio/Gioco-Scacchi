#include<iostream>
#include<fstream>
using namespace std;

#ifndef SCACCHIERA_H
#define SCACCHIERA_H

//_________________________________ PEDINA ______________________________
class Pedina
{
private:
	int x, y;
	bool color;

public:
	Pedina();
	Pedina(int, int, bool);	//pos x, pos y, colore(true bianco, false nero)

	int getL() const {return x; }
	int getN() const {return y; }
	void setPos(int, int);
	bool getColor() const;

	virtual bool move(int, int);
	virtual ostream& operator<< (ostream& os);
	
	virtual bool checkPos();

	class InvalidPosition
	{
	};
};

//_________________________________ SCACCHIERA ______________________________
class Scacchiera
{
private:

	Pedina* matrice[8][8];

public:
	Scacchiera();

	
	ostream& operator<<(ostream& os);

	bool isEmpty(int x, int y) const { return matrice[x][y]==nullptr; }

	Pedina* getPedina(int x, int y) const { return (matrice[x][y]); }

	bool isScacco();
	bool isScaccoMatto();
	bool isPatta();
	
};


#endif