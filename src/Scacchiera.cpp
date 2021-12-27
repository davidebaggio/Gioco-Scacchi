// Luca Mainardi

#include "../include/Scacchiera.h"
#include "../include/Pezzi.h"

Scacchiera::Scacchiera() // posiziona pedine nella posizione di partenza
{
	bool g1 = true;
	Pedone p;
	Torre t;
	Cavallo c;
	Alfiere a;
	Regina d;
	Re r;
	Empty e;
	for (int i = 0; i < 8; i++)
	{
		if (i > 3)
			g1 = false;
		for (int j = 0; j < 8; j++)
		{
			if (i == 1) // fila di pedoni bianchi
			{
				p.setPos(i, j);
				p.setColor(g1);
				p.setName('p');
				matrice[i][j] = p;
			}
			else if (i == 6) // fila di pedoni neri
			{
				p.setPos(i, j);
				p.setColor(g1);
				p.setName('p');
				matrice[i][j] = p;
			}
			else if (i == 0) // fila con pedine bianche
			{
				if (j == 0 || j == 7)
				{
					t.setPos(i, j);
					t.setColor(g1);
					t.setName('t');
					matrice[i][j] = t;
				}
				if (j == 1 || j == 6)
				{
					c.setPos(i, j);
					c.setColor(g1);
					c.setName('c');
					matrice[i][j] = c;
				}
				if (j == 2 || j == 5)
				{
					a.setPos(i, j);
					a.setColor(g1);
					a.setName('a');
					matrice[i][j] = a;
				}
				if (j == 3)
				{
					d.setPos(i, j);
					d.setColor(g1);
					d.setName('d');
					matrice[i][j] = d;
				}
				if (j == 4)
				{
					r.setPos(i, j);
					r.setColor(g1);
					r.setName('r');
					matrice[i][j] = r;
				}
			}
			else if (i == 7) // fila con pedine nere
			{
				if (j == 0 || j == 7)
				{
					t.setPos(i, j);
					t.setColor(g1);
					t.setName('t');
					matrice[i][j] = t;
				}
				if (j == 1 || j == 6)
				{
					c.setPos(i, j);
					c.setColor(g1);
					c.setName('c');
					matrice[i][j] = c;
				}
				if (j == 2 || j == 5)
				{
					a.setPos(i, j);
					a.setColor(g1);
					a.setName('a');
					matrice[i][j] = a;
				}
				if (j == 3)
				{
					d.setPos(i, j);
					d.setColor(g1);
					d.setName('d');
					matrice[i][j] = d;
				}
				if (j == 4)
				{
					r.setPos(i, j);
					r.setColor(g1);
					r.setName('r');
					matrice[i][j] = r;
				}
			}
			else
			{
				e.setPos(i, j);
				e.setName(' ');
				matrice[i][j] = e;
			}

			// cout << matrice[i][j].getName() << " ";
		}
		// cout << "\n";
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
		os << 8 - i << "  ";
		for (int j = 0; j < 8; j++)
		{
			os << sca.getPedina(i, j).getName() << " ";
		}
		os << "\n";
	}
	os << "\n   A B C D E F G H\n";
	// Pedina p = sca.getPedina(1, 1);
	/* os << 8 << " TCADRACT"
	   << "\n"
	   << 7 << " PPPPPPPP"
	   << "\n"
	   << 6 << "\n"
	   << 5 << "\n"
	   << 4 << " \n"
	   << 3 << "\n"
	   << 2 << " pppppppp"
	   << "\n"
	   << 1 << " tcadract"
	   << "\n"
	   << "  ABCDEFGH"
	   << "\n"; */
	return os;
}