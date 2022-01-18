// Melissa Maistro

#include "../include/Scacchiera.h"
using namespace std;

Pedina::Pedina(int l, int n, bool c, char na)
{
	x = l;
	y = n;
	color = c;
	setName(na);
	moveCount = 0;
}

void Pedina::setPos(int l, int n)
{
	x = l;
	y = n;
}

void Pedina::setColor(bool c)
{
	color = c;
}

void Pedina::setName(const char &n)
{
	if (!getColor())
		name = toupper(n);
	else
		name = n;
}

ostream &operator<<(ostream &os, const Pedina &ped)
{
	os << ped.getName();
	return os;
}
