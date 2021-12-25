// Luca Mainardi

#include "../include/Scacchiera.h"
#include "../include/Pezzi.h"

Scacchiera::Scacchiera() // posiziona pedine nella posizione di partenza
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (i == 1) // fila di pedoni bianchi
			{
				Pedina p = Pedone(j, i, true, 'p');
				matrice[i][j] = &p;
			}

			if (i == 0) // fila con pedine bianche
			{
				if (j == 0 || j == 7)
				{
					Pedina t = Torre(j, i, true, 't');
					matrice[i][j] = &t;
				}
				if (j == 1 || j == 6)
				{
					Pedina c = Cavallo(j, i, true, 'c');
					matrice[i][j] = &c;
				}
				if (j == 2 || j == 5)
				{
					Pedina a = Alfiere(j, i, true, 'a');
					matrice[i][j] = &a;
				}
				if (j == 3)
				{
					Pedina d = Regina(j, i, true, 'd');
					matrice[i][j] = &d;
				}
				if (j == 4)
				{
					Pedina r = Re(j, i, true, 'r');
					matrice[i][j] = &r;
				}
			}

			if (i == 7) // fila di pedoni neri
			{
				Pedina p = Pedone(j, i, false, 'p');
				matrice[i][j] = &p;
			}

			if (i == 7) // fila con pedine nere
			{
				if (j == 0 || j == 7)
				{
					Pedina t = Torre(j, i, false, 't');
					matrice[i][j] = &t;
				}
				if (j == 1 || j == 6)
				{
					Pedina c = Cavallo(j, i, false, 'c');
					matrice[i][j] = &c;
				}
				if (j == 2 || j == 5)
				{
					Pedina a = Alfiere(j, i, false, 'a');
					matrice[i][j] = &a;
				}
				if (j == 3)
				{
					Pedina d = Regina(j, i, false, 'd');
					matrice[i][j] = &d;
				}
				if (j == 4)
				{
					Pedina r = Re(i, j, false, 'r');
					matrice[i][j] = &r;
				}
			}
			else
				matrice[i][j] = nullptr;
		}
	}
}

bool Scacchiera::checkBoundaries(int px, int py)
{
	if (px < 0 || px > 8 || py < 0 || py > 8)
		throw InvalidIndex();
	else
		return true;
}

ostream &operator<<(ostream &os, const Scacchiera &sca)
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			os << sca.getPedina(i, j);
		}
	}
	return os;
}