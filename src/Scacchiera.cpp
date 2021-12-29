// Luca Mainardi

#include "../include/Scacchiera.h"
#include "../include/Pezzi.h"

Scacchiera::Scacchiera() // posiziona pedine nella posizione di partenza
{
	bool gWhite = false; // colore pedine
	// Pedone p;
	// Torre t;
	// Cavallo c;
	// Alfiere a;
	// Regina d;
	// Re r;
	// Empty e;
	for (int i = 0; i < 8; i++)
	{
		if (i > 3) // metà scacchiera
			gWhite = true;
		for (int j = 0; j < 8; j++)
		{
			if (i == 1) // fila di pedoni neri
			{
				// p.setPos(i, j);
				// p.setColor(gWhite);
				// p.setName('p');
				Pedone p(j, i, gWhite, 'p');
				matrice[i][j] = p;
			}
			else if (i == 6) // fila di pedoni bianchi
			{
				// p.setPos(i, j);
				// p.setColor(g1);
				// p.setName('p');
				Pedone p(j, i, gWhite, 'p');
				matrice[i][j] = p;
			}
			else if (i == 0) // fila con pedine nere
			{
				if (j == 0 || j == 7)
				{
					// t.setPos(i, j);
					// t.setColor(g1);
					// t.setName('t');
					Torre t(j, i, gWhite, 't');
					matrice[i][j] = t;
				}
				if (j == 1 || j == 6)
				{
					// c.setPos(i, j);
					// c.setColor(g1);
					// c.setName('c');
					Cavallo c(j, i, gWhite, 'c');
					matrice[i][j] = c;
				}
				if (j == 2 || j == 5)
				{
					// a.setPos(i, j);
					// a.setColor(g1);
					// a.setName('a');
					Alfiere a(j, i, gWhite, 'a');
					matrice[i][j] = a;
				}
				if (j == 3)
				{
					// d.setPos(i, j);
					// d.setColor(g1);
					// d.setName('d');
					Regina d(j, i, gWhite, 'd');
					matrice[i][j] = d;
				}
				if (j == 4)
				{
					// r.setPos(i, j);
					// r.setColor(g1);
					// r.setName('r');
					Re r(j, i, gWhite, 'r');
					matrice[i][j] = r;
				}
			}
			else if (i == 7) // fila con pedine bianche
			{
				if (j == 0 || j == 7)
				{
					// t.setPos(i, j);
					// t.setColor(g1);
					// t.setName('t');
					Torre t(j, i, gWhite, 't');
					matrice[i][j] = t;
				}
				if (j == 1 || j == 6)
				{
					// c.setPos(i, j);
					// c.setColor(g1);
					// c.setName('c');
					Cavallo c(j, i, gWhite, 'c');
					matrice[i][j] = c;
				}
				if (j == 2 || j == 5)
				{
					// a.setPos(i, j);
					// a.setColor(g1);
					// a.setName('a');
					Alfiere a(j, i, gWhite, 'a');
					matrice[i][j] = a;
				}
				if (j == 3)
				{
					// d.setPos(i, j);
					// d.setColor(g1);
					// d.setName('d');
					Regina d(j, i, gWhite, 'd');
					matrice[i][j] = d;
				}
				if (j == 4)
				{
					// r.setPos(i, j);
					// r.setColor(g1);
					// r.setName('r');
					Re r(j, i, gWhite, 'r');
					matrice[i][j] = r;
				}
			}
			else
			{
				// e.setPos(i, j);
				// e.setName(' ');
				Empty e(j, i, gWhite, ' ');
				matrice[i][j] = e;
			}
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

void Scacchiera::setPedina(Pedina p)
{
	matrice[p.getX()][p.getY()] = p;
}

bool Scacchiera::isScacco()
{
	int reBianco[2];
	int reNero[2];

	for (int i = 0; i < 8; i++) // trova posizioni re
	{
		for (int j = 0; j < 8; j++)
		{
			if (getPedina(j, i).getName() == 'r') // re bianco
			{
				reBianco[0] = j;
				reBianco[1] = i;
			}
			if (getPedina(j, i).getName() == 'R') // re nero
			{
				reBianco[0] = j;
				reBianco[1] = i;
			}
		}
	}

	bool scacco = false;

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			Pedina p = getPedina(j, i);

			if (p.getName() != 'e' && p.getColor()) // se c'è una pedina ed è bianca
			{
				if (p.getName() == 'p') // se è pedone bisogna controllare cattura, NON checkPos()
				{
					Pedone ped(j, i, p.getColor(), p.getName());
					scacco = ped.checkCattura(reNero[0], reNero[1]);
				}
				else
					scacco = p.checkPos(reNero[0], reNero[1]);
			}
			if (p.getName() != 'e' && !p.getColor()) // se c'è una pedina ed è nera
			{
				if (p.getName() == 'P') // se è pedone bisogna controllare cattura, NON checkPos()
				{
					Pedone ped(j, i, p.getColor(), p.getName());
					scacco = ped.checkCattura(reBianco[0], reBianco[1]);
				}
				else
					scacco = p.checkPos(reBianco[0], reBianco[1]);
			}
		}
	}
	return scacco;
}
