
#ifndef SCACCHIERA_H
#define SCACCHIERA_H

#include <iostream>
#include <fstream>
#include <cctype>
#include <vector>

using namespace std;

// class Scacchiera;
//_________________________________ PEDINA ______________________________
class Pedina
{
private:
	int x;
	int y;
	bool color;
	char name;
	int moveCount;

public:
	// Pedina();
	Pedina(int, int, bool, char); // pos x, pos y, colore(true bianco, false nero), lettera ref
	virtual ~Pedina() {}

	int getX() const { return x; }
	int getY() const { return y; }
	void setPos(int, int);
	bool getColor() const { return color; }
	void setColor(bool);
	void setName(const char &n);
	char getName() const { return name; }
	int getMoveCount() const { return moveCount; }
	void increaseCount() { moveCount++; }

	// virtual bool move(int, int, Scacchiera &);
	virtual bool checkPos(int destX, int destY, Pedina *matrice[8][8]) = 0;

	friend ostream &operator<<(ostream &os, const Pedina &);

	Pedina(const Pedina &) = delete;
	Pedina &operator=(const Pedina &) = delete;
};
//_________________________________ SCACCHIERA ______________________________

class Scacchiera
{
private:
	Pedina *matrice[8][8];

	bool KingsHaveValidPositions();
	int hasValidPositions(); // 0 se entrambi hanno pos valide
							 // 1 se bianco ha pos valida e nero no
							 // 2 se nero ha pos valida e bianco no
							 // 3 se nessuno ha pos valide

public:
	Scacchiera();
	~Scacchiera();

	// Pedina **getMatrice() { return matrice; }

	Pedina *getPedina(int x, int y) const { return matrice[x][y]; }
	void setPedina(Pedina *);
	bool isEmpty(int x, int y) const { return matrice[x][y] == nullptr; }

	void changePiece(int, int, Pedina *);
	void move(Pedina *p, int destX, int destY);

	// ritornano 0 se non e' scacco, 1 se bianco e' sotto scacco, 2 se nero e' sotto scacco
	int isScacco();
	int isScaccoMatto();
	bool isPatta();

	// MOSSE SPECIALI
};

ostream &operator<<(ostream &os, const Scacchiera &);

class InvalidIndex
{
};

class InvalidPosition
{
};

#endif