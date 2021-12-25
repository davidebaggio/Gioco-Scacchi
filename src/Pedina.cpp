//Melissa Maistro

#include "../include/Scacchiera.h"
#include "../include/Pezzi.h"

Pedina::Pedina(int l, int n, bool c)
{
	x = l;
	y = n;
	color = c;
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

ostream& Pedina::operator<< (ostream& os)
{
	os << " ";
}