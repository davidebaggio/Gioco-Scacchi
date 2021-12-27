// Melissa Maistro

#include "../include/Scacchiera.h"

Pedina::Pedina(int l, int n, bool c, char na)
{
	x = l;
	y = n;
	color = c;
	setName(na);
}

void Pedina::setPos(int l, int n)
{
	x = l;
	y = n;
}

bool Pedina::getColor() const
{
	return color;
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

bool Pedina::move(int px, int py)
{
	return false;
}

bool Pedina::checkPos()
{
	return false;
}

ostream &operator<<(ostream &os, const Pedina &ped)
{
	os << ped.getName();
	return os;
}