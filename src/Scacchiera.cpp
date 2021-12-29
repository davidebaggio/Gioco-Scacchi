// Luca Mainardi

#include <fstream>
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
		if (i > 3) // meta' scacchiera
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
		os << i + 1 << "  ";
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

bool Scacchiera::isPatta()
{
	return false;
}

bool Scacchiera::isScaccoMatto()
{
	return false;
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

			if (p.getName() != 'e' && p.getColor()) // se c'e' una pedina ed e' bianca
			{
				scacco = p.checkPos(reNero[0], reNero[1], *this);
			}
			if (p.getName() != 'e' && !p.getColor()) // se c'e' una pedina ed e' nera
			{
				scacco = p.checkPos(reBianco[0], reBianco[1], *this);
			}
		}
	}
	return scacco;
}

bool Scacchiera::isScaccoMatto()
{
	if (!isScacco())
		return false;

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

	// ------------------------------- controllo scacco re bianco (provo a muovere re in tutte le direzioni)-------------------------------
	bool posValidaBianco = false;
	try
	{
		getPedina(reBianco[0], reBianco[1]).move(reBianco[0], reBianco[1] - 1, *this); // su
		getPedina(reBianco[0], reBianco[1] - 1).move(reBianco[0], reBianco[1], *this); // torna
		posValidaBianco = true;														   // esiste posizione valida
	}
	catch (const Pedina::InvalidPosition &e) // ignora eccezioni ma posValida rimane false
	{
	}

	try
	{
		getPedina(reBianco[0], reBianco[1]).move(reBianco[0] + 1, reBianco[1] - 1, *this); // su dx
		getPedina(reBianco[0] + 1, reBianco[1] - 1).move(reBianco[0], reBianco[1], *this); // torna
		posValidaBianco = true;
	}
	catch (const Pedina::InvalidPosition &e)
	{
	}

	try
	{
		getPedina(reBianco[0], reBianco[1]).move(reBianco[0] + 1, reBianco[1], *this); // dx
		getPedina(reBianco[0] + 1, reBianco[1]).move(reBianco[0], reBianco[1], *this); // torna
		posValidaBianco = true;
	}
	catch (const Pedina::InvalidPosition &e)
	{
	}

	try
	{
		getPedina(reBianco[0], reBianco[1]).move(reBianco[0] + 1, reBianco[1] + 1, *this); // giu dx
		getPedina(reBianco[0] + 1, reBianco[1] + 1).move(reBianco[0], reBianco[1], *this); // torna
		posValidaBianco = true;
	}
	catch (const Pedina::InvalidPosition &e)
	{
	}

	try
	{
		getPedina(reBianco[0], reBianco[1]).move(reBianco[0], reBianco[1] + 1, *this); // giu
		getPedina(reBianco[0], reBianco[1] + 1).move(reBianco[0], reBianco[1], *this); // torna
		posValidaBianco = true;
	}
	catch (const Pedina::InvalidPosition &e)
	{
	}

	try
	{
		getPedina(reBianco[0], reBianco[1]).move(reBianco[0] - 1, reBianco[1] + 1, *this); // giu sx
		getPedina(reBianco[0] - 1, reBianco[1] + 1).move(reBianco[0], reBianco[1], *this); // torna
		posValidaBianco = true;
	}
	catch (const Pedina::InvalidPosition &e)
	{
	}

	try
	{
		getPedina(reBianco[0], reBianco[1]).move(reBianco[0] - 1, reBianco[1], *this); // sx
		getPedina(reBianco[0] - 1, reBianco[1]).move(reBianco[0], reBianco[1], *this); // torna
		posValidaBianco = true;
	}
	catch (const Pedina::InvalidPosition &e)
	{
	}

	try
	{
		getPedina(reBianco[0], reBianco[1]).move(reBianco[0] - 1, reBianco[1] - 1, *this); // su sx
		getPedina(reBianco[0] - 1, reBianco[1] - 1).move(reBianco[0], reBianco[1], *this); // torna
		posValidaBianco = true;
	}
	catch (const Pedina::InvalidPosition &e)
	{
	}

	// ---------------------------------------------- controllo scaccomatto re nero ----------------------------------------------
	bool posValidaNero = false;

	try
	{
		getPedina(reNero[0], reNero[1]).move(reNero[0], reNero[1] - 1, *this); // su
		getPedina(reNero[0], reNero[1] - 1).move(reNero[0], reNero[1], *this); // torna
		posValidaNero = true;
	}
	catch (const Pedina::InvalidPosition &e)
	{
	}
	try
	{
		getPedina(reNero[0], reNero[1]).move(reNero[0] + 1, reNero[1] - 1, *this); // su dx
		getPedina(reNero[0] + 1, reNero[1] - 1).move(reNero[0], reNero[1], *this); // torna
		posValidaNero = true;
	}
	catch (const Pedina::InvalidPosition &e)
	{
	}
	try
	{
		getPedina(reNero[0], reNero[1]).move(reNero[0] + 1, reNero[1], *this); // dx
		getPedina(reNero[0] + 1, reNero[1]).move(reNero[0], reNero[1], *this); // torna
		posValidaNero = true;
	}
	catch (const Pedina::InvalidPosition &e)
	{
	}
	try
	{
		getPedina(reNero[0], reNero[1]).move(reNero[0] + 1, reNero[1] + 1, *this); // giu dx
		getPedina(reNero[0] + 1, reNero[1] + 1).move(reNero[0], reNero[1], *this); // torna
		posValidaNero = true;
	}
	catch (const Pedina::InvalidPosition &e)
	{
	}
	try
	{
		getPedina(reNero[0], reNero[1]).move(reNero[0], reNero[1] + 1, *this); // giu
		getPedina(reNero[0], reNero[1] + 1).move(reNero[0], reNero[1], *this); // torna
		posValidaNero = true;
	}
	catch (const Pedina::InvalidPosition &e)
	{
	}
	try
	{
		getPedina(reNero[0], reNero[1]).move(reNero[0] - 1, reNero[1] + 1, *this); // giu sx
		getPedina(reNero[0] - 1, reNero[1] + 1).move(reNero[0], reNero[1], *this); // torna
		posValidaNero = true;
	}
	catch (const Pedina::InvalidPosition &e)
	{
	}
	try
	{
		getPedina(reNero[0], reNero[1]).move(reNero[0] - 1, reNero[1], *this); // sx
		getPedina(reNero[0] - 1, reNero[1]).move(reNero[0], reNero[1], *this); // torna
		posValidaNero = true;
	}
	catch (const Pedina::InvalidPosition &e)
	{
	}
	try
	{
		getPedina(reNero[0], reNero[1]).move(reNero[0] - 1, reNero[1] - 1, *this); // su sx
		getPedina(reNero[0] - 1, reNero[1] - 1).move(reNero[0], reNero[1], *this); // torna
		posValidaNero = true;
	}
	catch (const Pedina::InvalidPosition &e)
	{
	}

	if (posValidaBianco || posValidaNero) // se esiste almeno una pos valida NON e' scacco matto
	{
		return false;
	}

	return true;
}

bool Scacchiera::isPatta()
{
	ifstream input("output.txt");

	// se il re non ha posizioni valide per muoversi ma NON e' scacco

	return true;
}

bool KingsHaveValidPositions(Scacchiera s)
{
	// cerco i due re nella scacchiera
	int reBianco[2];
	int reNero[2];

	for (int i = 0; i < 8; i++) // trova posizioni re
	{
		for (int j = 0; j < 8; j++)
		{
			if (s.getPedina(j, i).getName() == 'r') // re bianco
			{
				reBianco[0] = j;
				reBianco[1] = i;
			}
			if (s.getPedina(j, i).getName() == 'R') // re nero
			{
				reBianco[0] = j;
				reBianco[1] = i;
			}
		}
	}

	// ------------------------------- controllo posizioni valide re bianco (provo a muovere re in tutte le direzioni)-------------------------------
	bool posValidaBianco = false;
	try
	{
		s.getPedina(reBianco[0], reBianco[1]).move(reBianco[0], reBianco[1] - 1, s); // su
		s.getPedina(reBianco[0], reBianco[1] - 1).move(reBianco[0], reBianco[1], s); // torna
		posValidaBianco = true;														 // esiste posizione valida
	}
	catch (const Pedina::InvalidPosition &e) // ignora eccezioni ma posValida rimane false
	{
	}

	try
	{
		s.getPedina(reBianco[0], reBianco[1]).move(reBianco[0] + 1, reBianco[1] - 1, s); // su dx
		s.getPedina(reBianco[0] + 1, reBianco[1] - 1).move(reBianco[0], reBianco[1], s); // torna
		posValidaBianco = true;
	}
	catch (const Pedina::InvalidPosition &e)
	{
	}

	try
	{
		s.getPedina(reBianco[0], reBianco[1]).move(reBianco[0] + 1, reBianco[1], s); // dx
		s.getPedina(reBianco[0] + 1, reBianco[1]).move(reBianco[0], reBianco[1], s); // torna
		posValidaBianco = true;
	}
	catch (const Pedina::InvalidPosition &e)
	{
	}

	try
	{
		s.getPedina(reBianco[0], reBianco[1]).move(reBianco[0] + 1, reBianco[1] + 1, s); // giu dx
		s.getPedina(reBianco[0] + 1, reBianco[1] + 1).move(reBianco[0], reBianco[1], s); // torna
		posValidaBianco = true;
	}
	catch (const Pedina::InvalidPosition &e)
	{
	}

	try
	{
		s.getPedina(reBianco[0], reBianco[1]).move(reBianco[0], reBianco[1] + 1, s); // giu
		s.getPedina(reBianco[0], reBianco[1] + 1).move(reBianco[0], reBianco[1], s); // torna
		posValidaBianco = true;
	}
	catch (const Pedina::InvalidPosition &e)
	{
	}

	try
	{
		s.getPedina(reBianco[0], reBianco[1]).move(reBianco[0] - 1, reBianco[1] + 1, s); // giu sx
		s.getPedina(reBianco[0] - 1, reBianco[1] + 1).move(reBianco[0], reBianco[1], s); // torna
		posValidaBianco = true;
	}
	catch (const Pedina::InvalidPosition &e)
	{
	}

	try
	{
		s.getPedina(reBianco[0], reBianco[1]).move(reBianco[0] - 1, reBianco[1], s); // sx
		s.getPedina(reBianco[0] - 1, reBianco[1]).move(reBianco[0], reBianco[1], s); // torna
		posValidaBianco = true;
	}
	catch (const Pedina::InvalidPosition &e)
	{
	}

	try
	{
		s.getPedina(reBianco[0], reBianco[1]).move(reBianco[0] - 1, reBianco[1] - 1, s); // su sx
		s.getPedina(reBianco[0] - 1, reBianco[1] - 1).move(reBianco[0], reBianco[1], s); // torna
		posValidaBianco = true;
	}
	catch (const Pedina::InvalidPosition &e)
	{
	}

	// ---------------------------------------------- controllo posizioni valide re nero ----------------------------------------------
	bool posValidaNero = false;

	try
	{
		s.getPedina(reNero[0], reNero[1]).move(reNero[0], reNero[1] - 1, s); // su
		s.getPedina(reNero[0], reNero[1] - 1).move(reNero[0], reNero[1], s); // torna
		posValidaNero = true;
	}
	catch (const Pedina::InvalidPosition &e)
	{
	}
	try
	{
		s.getPedina(reNero[0], reNero[1]).move(reNero[0] + 1, reNero[1] - 1, s); // su dx
		s.getPedina(reNero[0] + 1, reNero[1] - 1).move(reNero[0], reNero[1], s); // torna
		posValidaNero = true;
	}
	catch (const Pedina::InvalidPosition &e)
	{
	}
	try
	{
		s.getPedina(reNero[0], reNero[1]).move(reNero[0] + 1, reNero[1], s); // dx
		s.getPedina(reNero[0] + 1, reNero[1]).move(reNero[0], reNero[1], s); // torna
		posValidaNero = true;
	}
	catch (const Pedina::InvalidPosition &e)
	{
	}
	try
	{
		s.getPedina(reNero[0], reNero[1]).move(reNero[0] + 1, reNero[1] + 1, s); // giu dx
		s.getPedina(reNero[0] + 1, reNero[1] + 1).move(reNero[0], reNero[1], s); // torna
		posValidaNero = true;
	}
	catch (const Pedina::InvalidPosition &e)
	{
	}
	try
	{
		s.getPedina(reNero[0], reNero[1]).move(reNero[0], reNero[1] + 1, s); // giu
		s.getPedina(reNero[0], reNero[1] + 1).move(reNero[0], reNero[1], s); // torna
		posValidaNero = true;
	}
	catch (const Pedina::InvalidPosition &e)
	{
	}
	try
	{
		s.getPedina(reNero[0], reNero[1]).move(reNero[0] - 1, reNero[1] + 1, s); // giu sx
		s.getPedina(reNero[0] - 1, reNero[1] + 1).move(reNero[0], reNero[1], s); // torna
		posValidaNero = true;
	}
	catch (const Pedina::InvalidPosition &e)
	{
	}
	try
	{
		s.getPedina(reNero[0], reNero[1]).move(reNero[0] - 1, reNero[1], s); // sx
		s.getPedina(reNero[0] - 1, reNero[1]).move(reNero[0], reNero[1], s); // torna
		posValidaNero = true;
	}
	catch (const Pedina::InvalidPosition &e)
	{
	}
	try
	{
		s.getPedina(reNero[0], reNero[1]).move(reNero[0] - 1, reNero[1] - 1, s); // su sx
		s.getPedina(reNero[0] - 1, reNero[1] - 1).move(reNero[0], reNero[1], s); // torna
		posValidaNero = true;
	}
	catch (const Pedina::InvalidPosition &e)
	{
	}

	if (posValidaBianco || posValidaNero) // se esiste almeno una pos valida
	{
		return true;
	}

	return false;
}