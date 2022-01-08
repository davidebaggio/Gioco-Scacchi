#include "../include/Scacchiera.h"
#include "../include/Pezzi.h"

void Scacchiera::promozione(ofstream &spec, Pedina *p, bool player)
{
	if (p->getColor())
	{
		cout << "\nPromozione del Pedone Bianco\n";
		if (player)
		{
			cout << "Inserire la pedina con il quale vogliamo promuovere:\n";
			char name;
			do
			{
				cin >> name;
			} while (name != 't' && name != 'c' && name != 'a' && name != 'd' && name != 'r');
			int x = p->getX();
			int y = p->getY();
			Pedina *temp;
			if (name == 't')
				temp = new Torre(x, y, player, name);
			if (name == 'c')
				temp = new Cavallo(x, y, player, name);
			if (name == 'a')
				temp = new Alfiere(x, y, player, name);
			if (name == 'd')
				temp = new Regina(x, y, player, name);
			if (name == 'r')
				temp = new Re(x, y, player, name);
			changePiece(x, y, temp);
			spec << temp->getName() << "\n";
		}
		else
		{
			int x = p->getX();
			int y = p->getY();
			Pedina *temp;
			if (y == 0)
				temp = new Regina(x, y, true, 'd');
			else
				temp = new Regina(x, y, false, 'd');
			changePiece(x, y, temp);
			spec << temp->getName() << "\n";
		}
	}
	else
	{
		cout << "\nPromozione del pedone Nero\n";
		int x = p->getX();
		int y = p->getY();
		Pedina *temp = new Regina(x, y, false, 'd');
		changePiece(x, y, temp);
		spec << temp->getName() << "\n";
	}
}

void Scacchiera::replayPromo(Pedina *p, string special, bool player)
{
	int x = p->getX();
	int y = p->getY();
	Pedina *temp;
	if (special == "t" || special == "T")
		temp = new Torre(x, y, player, special[0]);
	if (special == "c" || special == "C")
		temp = new Cavallo(x, y, player, special[0]);
	if (special == "a" || special == "A")
		temp = new Alfiere(x, y, player, special[0]);
	if (special == "d" || special == "D")
		temp = new Regina(x, y, player, special[0]);
	if (special == "r" || special == "R")
		temp = new Re(x, y, player, special[0]);
	changePiece(x, y, temp);
}

void Scacchiera::arrocco(int xi, int yi, int xf, int yf)
{
	if (xi == 4 && yi == 0 && yf == 0) // arrocco del nero
	{
		if (xf == 0) // arrocco lungo
		{
			// verifica condizioni
			if (isScacco() == 2) // arrocco non si puo' fare se re e' sotto scacco
			{
				throw InvalidPosition();
			}
			if (isEmpty(xi, yi) || isEmpty(xf, yf)) // se una delle due caselle e' vuota
			{
				throw InvalidPosition();
			}
			Pedina *re = getPedina(xi, yi);
			Pedina *torre = getPedina(xf, yf);
			if (re->getMoveCount() != 0 || torre->getMoveCount() != 0) // se le pedine hanno gia fatto movimenti non si puo' arroccare
			{
				throw InvalidPosition();
			}
			if (!isEmpty(1, 0) || !isEmpty(2, 0) || !isEmpty(3, 0)) // se una delle celle tra re e torre e' occupata non si puo' arroccare
			{
				throw InvalidPosition();
			}
			// esegue arrocco
			move(re, 3, 0); // move controlla anche se re va sotto scacco (lancia InvalidPosition)
			move(re, 2, 0);
			torre->setPos(3, 0);
			setPedina(torre);
			setPtr(0, 0);
			return;
		}
		else if (xf == 7) // arrocco corto
		{

			// verifica condizioni
			if (isScacco() == 2) // arrocco non si puo' fare se re e' sotto scacco
			{
				throw InvalidPosition();
			}
			if (isEmpty(xi, yi) || isEmpty(xf, yf)) // se una delle due caselle e' vuota
			{
				throw InvalidPosition();
			}
			Pedina *re = getPedina(xi, yi);
			Pedina *torre = getPedina(xf, yf);
			if (re->getMoveCount() != 0 || torre->getMoveCount() != 0) // se le pedine hanno gia fatto movimenti non si puo' arroccare
			{
				throw InvalidPosition();
			}
			if (!isEmpty(5, 0) || !isEmpty(6, 0)) // se una delle celle tra re e torre e' occupata non si puo' arroccare
			{
				throw InvalidPosition();
			}
			// esegue arrocco
			move(re, 5, 0); // move controlla anche se re va sotto scacco (lancia InvalidPosition)
			move(re, 6, 0);
			torre->setPos(5, 0);
			setPedina(torre);
			setPtr(7, 0);
			return;
		}
		else // altre xf non valide
		{
			throw InvalidPosition();
		}
	}
	else if (xi == 4 && yi == 7 && yf == 7) // arrocco del bianco
	{
		if (xf == 0) // arrocco lungo
		{

			// verifica condizioni
			if (isScacco() == 1) // arrocco non si puo' fare se re e' sotto scacco
			{
				throw InvalidPosition();
			}
			if (isEmpty(xi, yi) || isEmpty(xf, yf)) // se una delle due caselle e' vuota
			{
				throw InvalidPosition();
			}
			Pedina *re = getPedina(xi, yi);
			Pedina *torre = getPedina(xf, yf);
			if (re->getMoveCount() != 0 || torre->getMoveCount() != 0) // se le pedine hanno gia fatto movimenti non si puo' arroccare
			{
				throw InvalidPosition();
			}
			if (!isEmpty(1, 7) || !isEmpty(2, 7) || !isEmpty(3, 7)) // se una delle celle tra re e torre e' occupata non si puo' arroccare
			{
				throw InvalidPosition();
			}
			// esegue arrocco
			move(re, 3, 7); // move controlla anche se re va sotto scacco (lancia InvalidPosition)
			move(re, 2, 7);
			torre->setPos(3, 7);
			setPedina(torre);
			setPtr(0, 7);
			/* matrice[3][7] = torre; // sposta torre
			matrice[0][7] = nullptr; */
			return;
		}
		else if (xf == 7) // arrocco corto
		{

			// verifica condizioni
			if (isScacco() == 1) // arrocco non si puo' fare se re e' sotto scacco
			{
				throw InvalidPosition();
			}
			if (isEmpty(xi, yi) || isEmpty(xf, yf)) // se una delle due caselle e' vuota
			{
				throw InvalidPosition();
			}
			Pedina *re = getPedina(xi, yi);
			Pedina *torre = getPedina(xf, yf);
			if (re->getMoveCount() != 0 || torre->getMoveCount() != 0) // se le pedine hanno gia fatto movimenti non si puo' arroccare
			{
				throw InvalidPosition();
			}
			if (!isEmpty(5, 7) || !isEmpty(6, 7)) // se una delle celle tra re e torre e' occupata non si puo' arroccare
			{
				throw InvalidPosition();
			}
			// esegue arrocco
			move(re, 5, 7); // move controlla anche se re va sotto scacco (lancia InvalidPosition)
			move(re, 6, 7);
			torre->setPos(5, 7);
			setPedina(torre);
			setPtr(7, 7);
			/* matrice[5][7] = torre; // sposta torre
			matrice[7][7] = nullptr; */
			return;
		}
		else
		{
			throw InvalidPosition();
		}
	}
	else // tutti i casi non validi
	{
		throw InvalidPosition();
	}
}

void Scacchiera::enPassant(Pedina *p, int xf, int yf)
{
	// salva coordinate di partenza
	int xi = p->getX();
	int yi = p->getY();
	// sposta pedina e elimina quella mangiata
	p->setPos(xf, yf);
	delete matrice[xf][yf];
	matrice[xf][yf] = p;
	matrice[xi][yi] = nullptr;
}
