// Melissa Maistro

#include "../include/Scacchiera.h"

Pedina::Pedina()
{
	x = -1;
	y = -1;
	color = false;
	name = 'e';
}

Pedina::Pedina(int l, int n, bool c, char na)
{
	x = l;
	y = n;
	color = c;
	setName(na);
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

bool Pedina::getColor() const
{
	return color;
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

char Pedina::getName() const
{
	return name;
}

bool move(Pedina &p, int px, int py, Scacchiera &sca)
{
	return false;
}

bool checkPos(Pedina &p, int, int, Scacchiera &)
{
	return false;
}

ostream &operator<<(ostream &os, const Pedina &ped)
{
	os << ped.name;
	return os;
}