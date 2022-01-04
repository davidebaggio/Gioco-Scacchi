// Melissa Maistro

#include "../include/Scacchiera.h"

/*
Pedina::Pedina()
{
	x = -1;
	y = -1;
	color = false;
	name = 'e';
	firstMove = true;
}
*/

Pedina::Pedina(int l, int n, bool c, char na)
{
	x = l;
	y = n;
	color = c;
	setName(na);
	firstMove = true;
}



/* Pedina::Pedina(const Pedina &ped)
{
	x = ped.getX();
	y = ped.getY();
	color = ped.getColor();
	name = ped.getName();
} */

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
