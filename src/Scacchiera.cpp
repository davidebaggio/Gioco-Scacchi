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
		cout << "Pedina : " << getPedina(j, i)->getName() << " mangiata\n";
		delete matrice[j][i];
	}

	int x = p->getX();
	int y = p->getY();

	p->setPos(j, i); // aggiorna coordinate della pedina

	matrice[j][i] = p;		 // aggiorna matrice
	matrice[x][y] = nullptr; // libera cella di partenza

	p->increaseCount();
}

int Scacchiera::isScacco()
{
	int reBiancoX, reBiancoY;
	int reNeroX, reNeroY;

	for (int i = 0; i < 8; i++) // trova posizioni re
	{
		for (int j = 0; j < 8; j++)
		{
			if (!isEmpty(j, i))
			{
				if (getPedina(j, i)->getName() == 'r') // re bianco
				{
					reBiancoX = j;
					reBiancoY = i;
				}
				if (getPedina(j, i)->getName() == 'R') // re nero
				{
					reNeroX = j;
					reNeroY = i;
				}
			}
		}
	}

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (!isEmpty(j, i))
			{
				Pedina *p = getPedina(j, i);

				if (p->getColor()) // se c'e' una pedina ed e' bianca
				{
					if (p->checkPos(reNeroX, reNeroY, matrice)) // scacco al nero
						return 2;
				}
				if (!p->getColor()) // se c'e' una pedina ed e' nera
				{
					if (p->checkPos(reBiancoX, reBiancoY, matrice)) // scacco al bianco
						return 1;
				}
			}
		}
	}
	return 0; // nessuno scacco
}

int Scacchiera::isScaccoMatto()
{
	if (isScacco() != 0)
	{
		if (hasValidPositions() == 2) // bianco non ha pos valide
			return 1;				  // scacco matto al bianco

		else if (hasValidPositions() == 1) // nero non ha pos valide
			return 2;					   // scacco matto al nero

		else // scacco non matto
			return 0;
	}

	return 0; // se non e' scacco
}

bool Scacchiera::isPatta()
{
	if (isScacco() == 0 && hasValidPositions() != 0) // se non è scacco e uno dei due non ha pos valide
	{
		return true;
	}
	return false;
	// da finire (tre mosse ripetute) <---------------------------------
}

bool Scacchiera::KingsHaveValidPositions()
{
	// cerco i due re nella scacchiera
	int reBiancoX, reBiancoY;
	int reNeroX, reNeroY;

	for (int i = 0; i < 8; i++) // trova posizioni re
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
	}

	// ------------------------------- controllo posizioni valide re bianco (provo a muovere re in tutte le direzioni)-------------------------------
	bool posValidaBianco = false;
	try
	{
		move((getPedina(reBiancoX, reBiancoY)), reBiancoX, reBiancoY - 1); // su
		move((getPedina(reBiancoX, reBiancoY - 1)), reBiancoX, reBiancoY); // torna
		posValidaBianco = true;											   // esiste posizione valida
	}
	catch (const InvalidPosition &e) // ignora eccezioni ma posValida rimane false
	{
	}

	try
	{
		move((getPedina(reBiancoX, reBiancoY)), reBiancoX + 1, reBiancoY - 1); // su dx
		move((getPedina(reBiancoX + 1, reBiancoY - 1)), reBiancoX, reBiancoY); // torna
		posValidaBianco = true;
	}
	catch (const InvalidPosition &e)
	{
	}

	try
	{
		move((getPedina(reBiancoX, reBiancoY)), reBiancoX + 1, reBiancoY); // dx
		move((getPedina(reBiancoX + 1, reBiancoY)), reBiancoX, reBiancoY); // torna
		posValidaBianco = true;
	}
	catch (const InvalidPosition &e)
	{
	}

	try
	{
		move((getPedina(reBiancoX, reBiancoY)), reBiancoX + 1, reBiancoY + 1); // giu dx
		move((getPedina(reBiancoX + 1, reBiancoY + 1)), reBiancoX, reBiancoY); // torna
		posValidaBianco = true;
	}
	catch (const InvalidPosition &e)
	{
	}

	try
	{
		move((getPedina(reBiancoX, reBiancoY)), reBiancoX, reBiancoY + 1); // giu
		move((getPedina(reBiancoX, reBiancoY + 1)), reBiancoX, reBiancoY); // torna
		posValidaBianco = true;
	}
	catch (const InvalidPosition &e)
	{
	}

	try
	{
		move((getPedina(reBiancoX, reBiancoY)), reBiancoX - 1, reBiancoY - 1); // giu sx
		move((getPedina(reBiancoX - 1, reBiancoY - 1)), reBiancoX, reBiancoY); // torna
		posValidaBianco = true;
	}
	catch (const InvalidPosition &e)
	{
	}

	try
	{
		move((getPedina(reBiancoX, reBiancoY)), reBiancoX - 1, reBiancoY); // sx
		move((getPedina(reBiancoX - 1, reBiancoY)), reBiancoX, reBiancoY); // torna
		posValidaBianco = true;
	}
	catch (const InvalidPosition &e)
	{
	}

	try
	{
		move((getPedina(reBiancoX, reBiancoY)), reBiancoX - 1, reBiancoY - 1); // su sx
		move((getPedina(reBiancoX - 1, reBiancoY - 1)), reBiancoX, reBiancoY); // torna
		posValidaBianco = true;
	}
	catch (const InvalidPosition &e)
	{
	}

	// 	// ---------------------------------------------- controllo posizioni valide re nero ----------------------------------------------
	bool posValidaNero = false;

	try
	{
		move((getPedina(reNeroX, reNeroY)), reNeroX, reNeroY - 1); // su
		move((getPedina(reNeroX, reNeroY - 1)), reNeroX, reNeroY); // torna
		posValidaNero = true;
	}
	catch (const InvalidPosition &e)
	{
	}
	try
	{
		move((getPedina(reNeroX, reNeroY)), reNeroX + 1, reNeroY - 1); // su dx
		move((getPedina(reNeroX + 1, reNeroY - 1)), reNeroX, reNeroY); // torna
		posValidaNero = true;
	}
	catch (const InvalidPosition &e)
	{
	}
	try
	{
		move((getPedina(reNeroX, reNeroY)), reNeroX + 1, reNeroY); // dx
		move((getPedina(reNeroX + 1, reNeroY)), reNeroX, reNeroY); // torna
		posValidaNero = true;
	}
	catch (const InvalidPosition &e)
	{
	}
	try
	{
		move((getPedina(reNeroX, reNeroY)), reNeroX + 1, reNeroY + 1); // giu dx
		move((getPedina(reNeroX + 1, reNeroY + 1)), reNeroX, reNeroY); // torna
		posValidaNero = true;
	}
	catch (const InvalidPosition &e)
	{
	}
	try
	{
		move((getPedina(reNeroX, reNeroY)), reNeroX, reNeroY + 1); // giu
		move((getPedina(reNeroX, reNeroY + 1)), reNeroX, reNeroY); // torna
		posValidaNero = true;
	}
	catch (const InvalidPosition &e)
	{
	}
	try
	{
		move((getPedina(reNeroX, reNeroY)), reNeroX - 1, reNeroY + 1); // giu sx
		move((getPedina(reNeroX - 1, reNeroY + 1)), reNeroX, reNeroY); // torna
		posValidaNero = true;
	}
	catch (const InvalidPosition &e)
	{
	}
	try
	{
		move((getPedina(reNeroX, reNeroY)), reNeroX - 1, reNeroY); // sx
		move((getPedina(reNeroX - 1, reNeroY)), reNeroX, reNeroY); // torna
		posValidaNero = true;
	}
	catch (const InvalidPosition &e)
	{
	}
	try
	{
		move((getPedina(reNeroX, reNeroY)), reNeroX - 1, reNeroY - 1); // su sx
		move((getPedina(reNeroX - 1, reNeroY - 1)), reNeroX, reNeroY); // torna
		posValidaNero = true;
	}
	catch (const InvalidPosition &e)
	{
	}

	if (posValidaBianco || posValidaNero) // se esiste almeno una pos valida
	{
		return true;
	}

	return true;
}

int Scacchiera::hasValidPositions()
{
	// esamina ogni pedina
	bool biancoHasPosition;
	bool neroHasPosition;

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (!isEmpty(j, i))
			{
				Pedina *p = matrice[j][i];
				// prova tutti i movimenti della pedina esaminata e vede se è scacco
				for (int y = 0; y < 8; y++)
				{
					for (int x = 0; x < 8; x++)
					{
						if (p->getColor()) // se è bianca
						{
							Pedina *temp = matrice[x][y];
							// prova movimento (NON si puo fare move perche mangerebbe le pedine)
							matrice[x][y] = matrice[j][i];
							matrice[j][i] = nullptr;
							biancoHasPosition = (isScacco() != 1);
							// torna indietro
							matrice[j][i] = matrice[x][y];
							matrice[x][y] = temp;
						}

						if (!p->getColor()) // se è nera
						{
							Pedina *temp = matrice[x][y];
							// prova movimento (NON si puo fare move perche mangerebbe le pedine)
							matrice[x][y] = matrice[j][i];
							matrice[j][i] = nullptr;
							neroHasPosition = (isScacco() != 2);
							// torna indietro
							matrice[j][i] = matrice[x][y];
							matrice[x][y] = temp;
						}
					}
				}
			}
		}
	}
	if (neroHasPosition && biancoHasPosition)
		return 0;
	else if (!neroHasPosition && biancoHasPosition)
		return 1;
	else if (neroHasPosition && !biancoHasPosition)
		return 2;
	else
		return 3;
}
