//#include "Header.h"
#ifndef PEDINA_H
#define PEDINA_H

//_________________________________ PEDINA ______________________________
class Pedina
{
private:
	int x;
	int y;
	bool color;
	char name;

public:
	Pedina();
	Pedina(int, int, bool, char); // pos x, pos y, colore(true bianco, false nero), lettera ref

	int getX() const { return x; }
	int getY() const { return y; }
	void setPos(int, int);
	bool getColor() const;
	void setColor(bool);
	void setName(const char &n);
	char getName() const;

	virtual bool move(int, int, Scacchiera &);
	virtual bool checkPos(int, int, Scacchiera &);

	friend ostream &operator<<(ostream &os, const Pedina &);

	class InvalidPosition
	{
	};
};
#endif