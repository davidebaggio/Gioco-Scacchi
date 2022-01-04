// Luca Mainardi

#include <fstream>
#include "../include/Scacchiera.h"
#include "../include/Pezzi.h"

Scacchiera::Scacchiera() // posiziona pedine nella posizione di partenza
{
	bool gWhite = false; // colore pedine
	for (int i = 0; i < 8; i++)
	{
		if (i > 3) // meta' scacchiera
			gWhite = true;
		for (int j = 0; j < 8; j++)
		{
			if (i == 1) // fila di pedoni neri
			{
				matrice[j][i] = new Pedone(j, i, gWhite, 'p');
			}
			else if (i == 6) // fila di pedoni bianchi
			{
				matrice[j][i] = new Pedone(j, i, gWhite, 'p');
			}
			else if (i == 0) // fila con pedine nere
			{
				if (j == 0 || j == 7)
				{
					matrice[j][i] = new Torre(j, i, gWhite, 't');
				}
				if (j == 1 || j == 6)
				{
					matrice[j][i] = new Cavallo(j, i, gWhite, 'c');
				}
				if (j == 2 || j == 5)
				{
					matrice[j][i] = new Alfiere(j, i, gWhite, 'a');
				}
				if (j == 3)
				{
					matrice[j][i] = new Regina(j, i, gWhite, 'd');
				}
				if (j == 4)
				{
					matrice[j][i] = new Re(j, i, gWhite, 'r');
				}
			}
			else if (i == 7) // fila con pedine bianche
			{
				if (j == 0 || j == 7)
				{
					matrice[j][i] = new Torre(j, i, gWhite, 't');
				}
				if (j == 1 || j == 6)
				{
					matrice[j][i] = new Cavallo(j, i, gWhite, 'c');
				}
				if (j == 2 || j == 5)
				{
					matrice[j][i] = new Alfiere(j, i, gWhite, 'a');
				}
				if (j == 3)
				{
					matrice[j][i] = new Regina(j, i, gWhite, 'd');
				}
				if (j == 4)
				{
					matrice[j][i] = new Re(j, i, gWhite, 'r');
				}
			}
			else
			{
				matrice[j][i] = nullptr;
			}
		}
	}
}

Scacchiera::~Scacchiera()
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			delete matrice[i][j];
			matrice[i][j] = nullptr;
		}
	}
}

ostream &operator<<(ostream &os, const Scacchiera &sca)
{
	for (int i = 0; i < 8; i++)
	{
		os << i + 1 << "  ";
		for (int j = 0; j < 8; j++)
		{
			if (sca.getPedina(j, i) == nullptr)
				os << "  ";
			else
				os << sca.getPedina(j, i)->getName() << " ";
		}
		os << "\n";
	}
	os << "\n   A B C D E F G H\n";

	return os;
}

void Scacchiera::setPedina(Pedina *p)
{
	matrice[p->getX()][p->getY()] = p;
}

void Scacchiera::move(Pedina *p, int j, int i)
{
	if (!(p->checkPos(j, i, matrice)))
		throw InvalidPosition();

	if (!isEmpty(j, i)) // dealloca memoria della pedina mangiata
	{
		cout << "Pedina : " << matrice[j][i]->getName() << " mangiata\n";
		delete matrice[j][i];
	}

	int x = p->getX();
	int y = p->getY();

	p->setPos(j, i); // aggiorna coordinate della pedina

	matrice[j][i] = p;		 // aggiorna matrice
	matrice[x][y] = nullptr; // libera cella di partenza
}

bool Scacchiera::isScacco()
{
	int reBianco[2];
	int reNero[2];

	/* for (int i = 0; i < 8; i++) // trova posizioni re
	{
		for (int j = 0; j < 8; j++)
		{
			if (getPedina(j, i)->getName() == 'r') // re bianco
			{
				reBianco[0] = j;
				reBianco[1] = i;
			}
			if (getPedina(j, i)->getName() == 'R') // re nero
			{
				reNero[0] = j;
				reNero[1] = i;
			}
		}
	}

	bool scacco = false;

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			Pedina *p = getPedina(j, i);

			if (p != nullptr && p->getColor()) // se c'e' una pedina ed e' bianca
			{
				scacco = p->checkPos(reNero[0], reNero[1], matrice);
			}
			if (p != nullptr && !p->getColor()) // se c'e' una pedina ed e' nera
			{
				scacco = p->checkPos(reBianco[0], reBianco[1], matrice);
			}
		}
	} */
	return false;
}

bool Scacchiera::isScaccoMatto()
{
	if (!isScacco())
		return false;

	/* int reBianco[2];
	int reNero[2];

	for (int i = 0; i < 8; i++) // trova posizioni re
	{
		for (int j = 0; j < 8; j++)
		{
			if ((*getPedina(j, i)).getName() == 'r') // re bianco
			{
				reBianco[0] = j;
				reBianco[1] = i;
			}
			if ((*getPedina(j, i)).getName() == 'R') // re nero
			{
				reNero[0] = j;
				reNero[1] = i;
			}
		}
	} */

	// 	// ------------------------------- controllo scacco re bianco (provo a muovere re in tutte le direzioni)-------------------------------
	// 	bool posValidaBianco = false;
	// 	try
	// 	{
	// 		(*getPedina(reBianco[0], reBianco[1])).move(reBianco[0], reBianco[1] - 1, *this); // su
	// 		(*getPedina(reBianco[0], reBianco[1] - 1)).move(reBianco[0], reBianco[1], *this); // torna
	// 		posValidaBianco = true;														   // esiste posizione valida
	// 	}
	// 	catch (const Pedina::InvalidPosition &e) // ignora eccezioni ma posValida rimane false
	// 	{
	// 	}

	// 	try
	// 	{
	// 		(*getPedina(reBianco[0], reBianco[1])).move(reBianco[0] + 1, reBianco[1] - 1, *this); // su dx
	// 		(*getPedina(reBianco[0] + 1, reBianco[1] - 1)).move(reBianco[0], reBianco[1], *this); // torna
	// 		posValidaBianco = true;
	// 	}
	// 	catch (const Pedina::InvalidPosition &e)
	// 	{
	// 	}

	// 	try
	// 	{
	// 		(*getPedina(reBianco[0], reBianco[1])).move(reBianco[0] + 1, reBianco[1], *this); // dx
	// 		(*getPedina(reBianco[0] + 1, reBianco[1])).move(reBianco[0], reBianco[1], *this); // torna
	// 		posValidaBianco = true;
	// 	}
	// 	catch (const Pedina::InvalidPosition &e)
	// 	{
	// 	}

	// 	try
	// 	{
	// 		(*getPedina(reBianco[0], reBianco[1])).move(reBianco[0] + 1, reBianco[1] + 1, *this); // giu dx
	// 		(*getPedina(reBianco[0] + 1, reBianco[1] + 1)).move(reBianco[0], reBianco[1], *this); // torna
	// 		posValidaBianco = true;
	// 	}
	// 	catch (const Pedina::InvalidPosition &e)
	// 	{
	// 	}

	// 	try
	// 	{
	// 		(*getPedina(reBianco[0], reBianco[1])).move(reBianco[0], reBianco[1] + 1, *this); // giu
	// 		(*getPedina(reBianco[0], reBianco[1] + 1)).move(reBianco[0], reBianco[1], *this); // torna
	// 		posValidaBianco = true;
	// 	}
	// 	catch (const Pedina::InvalidPosition &e)
	// 	{
	// 	}

	// 	try
	// 	{
	// 		(*getPedina(reBianco[0], reBianco[1])).move(reBianco[0] - 1, reBianco[1] + 1, *this); // giu sx
	// 		(*getPedina(reBianco[0] - 1, reBianco[1] + 1)).move(reBianco[0], reBianco[1], *this); // torna
	// 		posValidaBianco = true;
	// 	}
	// 	catch (const Pedina::InvalidPosition &e)
	// 	{
	// 	}

	// 	try
	// 	{
	// 		(*getPedina(reBianco[0], reBianco[1])).move(reBianco[0] - 1, reBianco[1], *this); // sx
	// 		(*getPedina(reBianco[0] - 1, reBianco[1])).move(reBianco[0], reBianco[1], *this); // torna
	// 		posValidaBianco = true;
	// 	}
	// 	catch (const Pedina::InvalidPosition &e)
	// 	{
	// 	}

	// 	try
	// 	{
	// 		(*getPedina(reBianco[0], reBianco[1])).move(reBianco[0] - 1, reBianco[1] - 1, *this); // su sx
	// 		(*getPedina(reBianco[0] - 1, reBianco[1] - 1)).move(reBianco[0], reBianco[1], *this); // torna
	// 		posValidaBianco = true;
	// 	}
	// 	catch (const Pedina::InvalidPosition &e)
	// 	{
	// 	}

	// 	// ---------------------------------------------- controllo scaccomatto re nero ----------------------------------------------
	// 	bool posValidaNero = false;

	// 	try
	// 	{
	// 		(*getPedina(reNero[0], reNero[1])).move(reNero[0], reNero[1] - 1, *this); // su
	// 		(*getPedina(reNero[0], reNero[1] - 1)).move(reNero[0], reNero[1], *this); // torna
	// 		posValidaNero = true;
	// 	}
	// 	catch (const Pedina::InvalidPosition &e)
	// 	{
	// 	}
	// 	try
	// 	{
	// 		(*getPedina(reNero[0], reNero[1])).move(reNero[0] + 1, reNero[1] - 1, *this); // su dx
	// 		(*getPedina(reNero[0] + 1, reNero[1] - 1)).move(reNero[0], reNero[1], *this); // torna
	// 		posValidaNero = true;
	// 	}
	// 	catch (const Pedina::InvalidPosition &e)
	// 	{
	// 	}
	// 	try
	// 	{
	// 		(*getPedina(reNero[0], reNero[1])).move(reNero[0] + 1, reNero[1], *this); // dx
	// 		(*getPedina(reNero[0] + 1, reNero[1])).move(reNero[0], reNero[1], *this); // torna
	// 		posValidaNero = true;
	// 	}
	// 	catch (const Pedina::InvalidPosition &e)
	// 	{
	// 	}
	// 	try
	// 	{
	// 		(*getPedina(reNero[0], reNero[1])).move(reNero[0] + 1, reNero[1] + 1, *this); // giu dx
	// 		(*getPedina(reNero[0] + 1, reNero[1] + 1)).move(reNero[0], reNero[1], *this); // torna
	// 		posValidaNero = true;
	// 	}
	// 	catch (const Pedina::InvalidPosition &e)
	// 	{
	// 	}
	// 	try
	// 	{
	// 		(*getPedina(reNero[0], reNero[1])).move(reNero[0], reNero[1] + 1, *this); // giu
	// 		(*getPedina(reNero[0], reNero[1] + 1)).move(reNero[0], reNero[1], *this); // torna
	// 		posValidaNero = true;
	// 	}
	// 	catch (const Pedina::InvalidPosition &e)
	// 	{
	// 	}
	// 	try
	// 	{
	// 		(*getPedina(reNero[0], reNero[1])).move(reNero[0] - 1, reNero[1] + 1, *this); // giu sx
	// 		(*getPedina(reNero[0] - 1, reNero[1] + 1)).move(reNero[0], reNero[1], *this); // torna
	// 		posValidaNero = true;
	// 	}
	// 	catch (const Pedina::InvalidPosition &e)
	// 	{
	// 	}
	// 	try
	// 	{
	// 		(*getPedina(reNero[0], reNero[1])).move(reNero[0] - 1, reNero[1], *this); // sx
	// 		(*getPedina(reNero[0] - 1, reNero[1])).move(reNero[0], reNero[1], *this); // torna
	// 		posValidaNero = true;
	// 	}
	// 	catch (const Pedina::InvalidPosition &e)
	// 	{
	// 	}
	// 	try
	// 	{
	// 		(*getPedina(reNero[0], reNero[1])).move(reNero[0] - 1, reNero[1] - 1, *this); // su sx
	// 		(*getPedina(reNero[0] - 1, reNero[1] - 1)).move(reNero[0], reNero[1], *this); // torna
	// 		posValidaNero = true;
	// 	}
	// 	catch (const Pedina::InvalidPosition &e)
	// 	{
	// 	}

	// 	if (posValidaBianco || posValidaNero) // se esiste almeno una pos valida NON e' scacco matto
	// 	{
	// 		return false;
	// 	}

	// 	return true;
	// }

	// bool Scacchiera::isPatta()
	// {
	// 	ifstream input("output.txt");

	// 	// se il re non ha posizioni valide per muoversi ma NON e' scacco

	return false;
}

bool Scacchiera::KingsHaveValidPositions()
{
	// cerco i due re nella scacchiera
	int reBiancoX, reBiancoY;
	int reNeroX, reNeroY;

	/* for (int i = 0; i < 8; i++) // trova posizioni re
	{
		for (int j = 0; j < 8; j++)
		{
			if ((*getPedina(j, i)).getName() == 'r') // re bianco
			{
				reBiancoX = j;
				reBiancoY = i;
			}
			if ((*getPedina(j, i)).getName() == 'R') // re nero
			{
				reNeroX = j;
				reNeroY = i;
			}
		}
	} */

	// ------------------------------- controllo posizioni valide re bianco (provo a muovere re in tutte le direzioni)-------------------------------
	// bool posValidaBianco = false;
	// try
	// {
	// 	move((*getPedina(reBiancoX,reBiancoY)), reBiancoX, reBiancoY-1)
	// 	(*s.getPedina(reBianco[0], reBianco[1])).move(reBianco[0], reBianco[1] - 1, s); // su
	// 	(*s.getPedina(reBianco[0], reBianco[1] - 1)).move(reBianco[0], reBianco[1], s); // torna
	// 	posValidaBianco = true;														 // esiste posizione valida
	// }
	// catch (const Pedina::InvalidPosition &e) // ignora eccezioni ma posValida rimane false
	// {
	// }

	// try
	// {
	// 	(*s.getPedina(reBianco[0], reBianco[1])).move(reBianco[0] + 1, reBianco[1] - 1, s); // su dx
	// 	(*s.getPedina(reBianco[0] + 1, reBianco[1] - 1)).move(reBianco[0], reBianco[1], s); // torna
	// 	posValidaBianco = true;
	// }
	// catch (const Pedina::InvalidPosition &e)
	// {
	// }

	// try
	// {
	// 	(*s.getPedina(reBianco[0], reBianco[1])).move(reBianco[0] + 1, reBianco[1], s); // dx
	// 	(*s.getPedina(reBianco[0] + 1, reBianco[1])).move(reBianco[0], reBianco[1], s); // torna
	// 	posValidaBianco = true;
	// }
	// catch (const Pedina::InvalidPosition &e)
	// {
	// }

	// try
	// {
	// 	(*s.getPedina(reBianco[0], reBianco[1])).move(reBianco[0] + 1, reBianco[1] + 1, s); // giu dx
	// 	(*s.getPedina(reBianco[0] + 1, reBianco[1] + 1)).move(reBianco[0], reBianco[1], s); // torna
	// 	posValidaBianco = true;
	// }
	// catch (const Pedina::InvalidPosition &e)
	// {
	// }

	// try
	// {
	// 	(*s.getPedina(reBianco[0], reBianco[1])).move(reBianco[0], reBianco[1] + 1, s); // giu
	// 	(*s.getPedina(reBianco[0], reBianco[1] + 1)).move(reBianco[0], reBianco[1], s); // torna
	// 	posValidaBianco = true;
	// }
	// catch (const Pedina::InvalidPosition &e)
	// {
	// }

	// try
	// {
	// 	(*s.getPedina(reBianco[0], reBianco[1])).move(reBianco[0] - 1, reBianco[1] + 1, s); // giu sx
	// 	(*s.getPedina(reBianco[0] - 1, reBianco[1] + 1)).move(reBianco[0], reBianco[1], s); // torna
	// 	posValidaBianco = true;
	// }
	// catch (const Pedina::InvalidPosition &e)
	// {
	// }

	// try
	// {
	// 	(*s.getPedina(reBianco[0], reBianco[1])).move(reBianco[0] - 1, reBianco[1], s); // sx
	// 	(*s.getPedina(reBianco[0] - 1, reBianco[1])).move(reBianco[0], reBianco[1], s); // torna
	// 	posValidaBianco = true;
	// }
	// catch (const Pedina::InvalidPosition &e)
	// {
	// }

	// try
	// {
	// 	(*s.getPedina(reBianco[0], reBianco[1])).move(reBianco[0] - 1, reBianco[1] - 1, s); // su sx
	// 	(*s.getPedina(reBianco[0] - 1, reBianco[1] - 1)).move(reBianco[0], reBianco[1], s); // torna
	// 	posValidaBianco = true;
	// }
	// catch (const Pedina::InvalidPosition &e)
	// {
	// }

	// 	// ---------------------------------------------- controllo posizioni valide re nero ----------------------------------------------
	// 	bool posValidaNero = false;

	// 	try
	// 	{
	// 		(*s.getPedina(reNero[0], reNero[1])).move(reNero[0], reNero[1] - 1, s); // su
	// 		(*s.getPedina(reNero[0], reNero[1] - 1)).move(reNero[0], reNero[1], s); // torna
	// 		posValidaNero = true;
	// 	}
	// 	catch (const Pedina::InvalidPosition &e)
	// 	{
	// 	}
	// 	try
	// 	{
	// 		(*s.getPedina(reNero[0], reNero[1])).move(reNero[0] + 1, reNero[1] - 1, s); // su dx
	// 		(*s.getPedina(reNero[0] + 1, reNero[1] - 1)).move(reNero[0], reNero[1], s); // torna
	// 		posValidaNero = true;
	// 	}
	// 	catch (const Pedina::InvalidPosition &e)
	// 	{
	// 	}
	// 	try
	// 	{
	// 		(*s.getPedina(reNero[0], reNero[1])).move(reNero[0] + 1, reNero[1], s); // dx
	// 		(*s.getPedina(reNero[0] + 1, reNero[1])).move(reNero[0], reNero[1], s); // torna
	// 		posValidaNero = true;
	// 	}
	// 	catch (const Pedina::InvalidPosition &e)
	// 	{
	// 	}
	// 	try
	// 	{
	// 		(*s.getPedina(reNero[0], reNero[1])).move(reNero[0] + 1, reNero[1] + 1, s); // giu dx
	// 		(*s.getPedina(reNero[0] + 1, reNero[1] + 1)).move(reNero[0], reNero[1], s); // torna
	// 		posValidaNero = true;
	// 	}
	// 	catch (const Pedina::InvalidPosition &e)
	// 	{
	// 	}
	// 	try
	// 	{
	// 		(*s.getPedina(reNero[0], reNero[1])).move(reNero[0], reNero[1] + 1, s); // giu
	// 		(*s.getPedina(reNero[0], reNero[1] + 1)).move(reNero[0], reNero[1], s); // torna
	// 		posValidaNero = true;
	// 	}
	// 	catch (const Pedina::InvalidPosition &e)
	// 	{
	// 	}
	// 	try
	// 	{
	// 		(*s.getPedina(reNero[0], reNero[1])).move(reNero[0] - 1, reNero[1] + 1, s); // giu sx
	// 		(*s.getPedina(reNero[0] - 1, reNero[1] + 1)).move(reNero[0], reNero[1], s); // torna
	// 		posValidaNero = true;
	// 	}
	// 	catch (const Pedina::InvalidPosition &e)
	// 	{
	// 	}
	// 	try
	// 	{
	// 		(*s.getPedina(reNero[0], reNero[1])).move(reNero[0] - 1, reNero[1], s); // sx
	// 		(*s.getPedina(reNero[0] - 1, reNero[1])).move(reNero[0], reNero[1], s); // torna
	// 		posValidaNero = true;
	// 	}
	// 	catch (const Pedina::InvalidPosition &e)
	// 	{
	// 	}
	// 	try
	// 	{
	// 		(*s.getPedina(reNero[0], reNero[1])).move(reNero[0] - 1, reNero[1] - 1, s); // su sx
	// 		(*s.getPedina(reNero[0] - 1, reNero[1] - 1)).move(reNero[0], reNero[1], s); // torna
	// 		posValidaNero = true;
	// 	}
	// 	catch (const Pedina::InvalidPosition &e)
	// 	{
	// 	}

	// 	if (posValidaBianco || posValidaNero) // se esiste almeno una pos valida
	// 	{
	// 		return true;
	// 	}

	return true;
}

bool Scacchiera::isPatta()
{
	return false;
}