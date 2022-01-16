// Luca Mainardi
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
		os << 8 - i << "  ";
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

void Scacchiera::changePiece(int x, int y, Pedina *p)
{
	delete matrice[x][y];
	matrice[x][y] = p;
}

void Scacchiera::setPtr(int x, int y)
{
	matrice[x][y] = nullptr;
}

void Scacchiera::move(Pedina *p, int j, int i) //(j,i) coordinate destinazione
{
	// controlla che casella (j,i) sia valida per p
	if (!(p->checkPos(j, i, matrice)))
		throw InvalidPosition();

	// memorizza eventuale pedina in (j,i)
	Pedina *temp = nullptr;
	if (!isEmpty(j, i))
	{
		temp = matrice[j][i];
	}
	// salva coordinate di partenza
	int x = p->getX();
	int y = p->getY();

	// provo a spostare la pedina
	p->setPos(j, i);		 // aggiorna coordinate della pedina
	matrice[j][i] = p;		 // aggiorna matrice
	matrice[x][y] = nullptr; // libera cella di partenza

	// controllo se dopo il movimento e' scacco, in tal caso non è possibile il movimento
	//  int color = 2;
	//  if(p->getColor())	//bianco e' colore 1 per lo scacco (se la pedina e' bianca devo controllare che bianco non sia sotto scacco)
	//  	color = 1;
	//  else
	//  	color = 2;			//nero è colore 2 per lo scacco	(se la pedina e' nera devo controllare che nero non sia sotto scacco)

	if (p->getColor()) // se e' bianca
	{
		if (isScacco() == 1) // se il giocatore che ha fatto la mossa e' sotto scacco	bisogna annullare la mossa e lanciare eccezione
		{
			matrice[x][y] = p;
			matrice[j][i] = temp;
			p->setPos(x, y);
			throw InvalidIndex();
		}
		else // non e' scacco
		{
			// dealloca la memoria della pedina mangiata
			if (temp != nullptr)
			{
				// cout << "\nPedina  " << temp->getName() << " mangiata\n";
				delete temp;
			}
		}
	}
	else // e' nera
	{
		if (isScacco() == 2) // se il giocatore che ha fatto la mossa e' sotto scacco	bisogna annullare la mossa e lanciare eccezione
		{
			matrice[x][y] = p;
			matrice[j][i] = temp;
			p->setPos(x, y);
			throw InvalidIndex();
		}
		else // non e' scacco
		{
			// dealloca la memoria della pedina mangiata
			if (temp != nullptr)
			{
				cout << "Pedina  " << temp->getName() << " mangiata\n";
				delete temp;
			}
		}
	}

	// if(isScacco() == color)	//se il giocatore che ha fatto la mossa e' sotto scacco	bisogna annullare la mossa e lanciare eccezione
	// {
	// 	matrice[x][y] = p;
	// 	matrice[j][i] = temp;
	// 	p->setPos(x, y);
	// 	throw InvalidPosition();
	// }
	// else	//non e' scacco
	// {
	// 	//dealloca la memoria della pedina mangiata
	// 	if(temp != nullptr)
	// 	{
	// 		cout << "Pedina  " << temp->getName() << " mangiata\n";
	// 		delete temp;
	// 	}

	// }

	// if (!isEmpty(j, i)) // dealloca memoria della pedina mangiata
	// {
	// 	cout << "Pedina : " << getPedina(j, i)->getName() << " mangiata\n";
	// 	delete matrice[j][i];
	// }

	// int x = p->getX();
	// int y = p->getY();

	// p->setPos(j, i); // aggiorna coordinate della pedina

	// matrice[j][i] = p;		 // aggiorna matrice
	// matrice[x][y] = nullptr; // libera cella di partenza

	p->increaseCount();
}

int Scacchiera::isScacco()
{
	int reBiancoX = -1, reBiancoY = -1;
	int reNeroX = -1, reNeroY = -1;
	/* int reBiancoX, reBiancoY;
	int reNeroX, reNeroY; */

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

	/* cout << "\n"
		 << reBiancoX << " " << reBiancoY << " " << reNeroX << " " << reNeroY << "\n";
	 */
	if (reBiancoX < 0 || reBiancoY < 0 || reNeroX < 0 || reNeroY < 0)
		return 0;

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (!isEmpty(j, i))
			{
				Pedina *p = getPedina(j, i);
				/* cout << "\n\n\n"
					 << j << "\n"
					 << i << "\n\n\n"; */
				if (p->getColor()) // se c'e' una pedina ed e' bianca
				{
					if (p->checkPos(reNeroX, reNeroY, matrice)) // scacco al nero
						return 2;
				}
				else // se c'e' una pedina ed e' nera
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

bool Scacchiera::isPatta(vector<string> &cmd)
{
	// patta per assenza di posizioni valide
	if (isScacco() == 0 && hasValidPositions() != 0) // se non è scacco e uno dei due non ha pos valide
	{
		return true;
	}

	// patta per mosse ripetute

	try
	{
		for (int i = 0; i < cmd.size(); i++) // verifica se tre mosse sono ripetute
		{
			string s1 = cmd.at(i);
			string s2 = cmd.at(i + 1);

			if (s1 == cmd.at(i + 4) && s1 == cmd.at(i + 8) && s2 == cmd.at(i + 5) && s2 == cmd.at(i + 9))
				return true;
		}
	}
	catch (out_of_range &e) // se indice non valido non puo' essere patta (fine del vector)
	{
		return false;
	}
	return false;
}

int Scacchiera::hasValidPositions()
{
	// esamina ogni pedina
	bool biancoHasPosition = false;
	bool neroHasPosition = false;

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
						// se la posizione e'valida per lo spostamento
						if (p->checkPos(x, y, matrice))
						{
							if (p->getColor()) // se è bianca
							{
								Pedina *temp = matrice[x][y];
								// prova movimento (NON si puo fare move() perche mangerebbe le pedine)
								matrice[x][y] = p;
								matrice[j][i] = nullptr;
								if (isScacco() != 1) // se non e' scacco allora il bianco ha almeno una posizione valida
								{
									biancoHasPosition = true;
								}
								// torna indietro
								matrice[j][i] = matrice[x][y];
								matrice[x][y] = temp;
							}
							else // se è nera
							{
								Pedina *temp = matrice[x][y];
								// prova movimento (NON si puo fare move() perche mangerebbe le pedine)
								matrice[x][y] = p;
								matrice[j][i] = nullptr;
								if (isScacco() != 2) // se non e' scacco allora il nero ha almeno una posizione valida
								{
									neroHasPosition = true;
								}
								// torna indietro
								matrice[j][i] = matrice[x][y];
								matrice[x][y] = temp;
							}
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
