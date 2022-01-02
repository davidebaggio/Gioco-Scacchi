// Melissa Maistro

#include "../include/Pezzi.h"
#include <iostream>
using namespace std;

//_______________________________________PEDONE___________________________________________
bool Pedone::move(int j, int i, Scacchiera &sca)
{
    if (Pedone::checkPos(j, i, sca))
        return true; // da finire...
    return false;
}

bool Pedone::checkPos(int j, int i, Scacchiera &sca) // controlla se puo' muoversi nella posizione data
{
    sca.checkBoundaries(j, i); // controllo indici
    if (getColor())            // se bianco
    {
        if (j == getX() && (i == getY() - 1)) // se avanti di 1
        {
            if (sca.getPedina(j, i)->getName() != 'e') // se c'e' una pedina non puo'
                return false;
            return true;
        }
        if (isFirstMove() && (j == getX() && i == getY() - 2)) // se prima mossa e avanti di 2
        {
            if ((sca.getPedina(j, i)->getName() != 'e') || (sca.getPedina(j, getY() - 1)->getName() != 'e'))
                return false; // se c'e' una pedina nella prima o seconda cella non puo'
            return true;
        }
        if ((i == getY() - 1 && (j == getX() - 1 || j == getX() + 1))) // se nelle due celle diagonali
        {
            if ((sca.getPedina(j, i)->getName() != 'e') && (!sca.getPedina(j, i)->getColor())) // solo se c'e' una pedina nera
                return true;
            return false;
        }
    }
    else // se nero
    {
        if (j == getX() && (i == getY() + 1)) // se avanti di 1
        {
            if (sca.getPedina(j, i)->getName() != 'e') // se c'e' una pedina non puo'
                return false;
            return true;
        }
        if (isFirstMove() && (j == getX() && i == getY() + 2)) // se prima mossa e avanti di 2
        {
            if ((sca.getPedina(j, i)->getName() != 'e') || (sca.getPedina(j, getY() + 1)->getName() != 'e'))
                return false; // se c'e' una pedina nella prima o seconda cella non puo'
            return true;
        }
        if ((i == getY() + 1 && (j == getX() - 1 || j == getX() + 1))) // se nelle due celle diagonali
        {
            if ((sca.getPedina(j, i)->getName() != 'e') && (sca.getPedina(j, i)->getColor())) // solo se c'e' una pedina bianca
                return true;
            return false;
        }
    }
    return false; // ritorna false se non puo' spostarsi nella casella
}

//_______________________________________CAVALLO___________________________________________
bool Cavallo::move(int px, int py, Scacchiera &sca)
{
    return false;
}

bool Cavallo::checkPos(int j, int i, Scacchiera &sca) // si sposta a L in tutte le direzioni anche se ci sono pedine
{                                                     // j colonne, i righe
    sca.checkBoundaries(j, i);
    if (j == getX() && (i == getY() - 1 || i == getY() - 2 || i == getY() + 1 || i == getY() + 2))
        return true;
    else if (j == getX() - 1 && (i == getY() || i == getY() - 1 || i == getY() - 2 || i == getY() + 1 || i == getY() + 2))
        return true;
    else if (j == getX() - 2 && (i == getY() || i == getY() - 1 || i == getY() + 1))
        return true;
    else if (j == getX() + 1 && (i == getY() || i == getY() - 1 || i == getY() - 2 || i == getY() + 1 || i == getY() + 2))
        return true;
    else if (j == getX() + 2 && (i == getY() || i == getY() - 1 || i == getY() + 1))
        return true;
    return false;
}

//_______________________________________ALFIERE___________________________________________
bool Alfiere::move(int px, int py, Scacchiera &sca)
{
    return false;
}

bool Alfiere::checkPos(int j, int i, Scacchiera &sca) // si muove nelle 4 diagonali
{
    sca.checkBoundaries(j, i);
    for (int n = 1; n < 8; n++) // diagonale nord-ovest
    {
        if ((sca.getPedina(getX() - n, getY() - n)->getName() != 'e') && (sca.getPedina(getX() - n, getY() - n)->getColor() == getColor()))
            break; // se c'e' una pedina ed e' del suo colore non va oltre
        if (j == getX() - n && i == getY() - n)
        {
            return true;
        }
    }
    for (int n = 1; n < 8; n++) // diagonale sud-ovest
    {
        if ((sca.getPedina(getX() - n, getY() + n)->getName() != 'e') && (sca.getPedina(getX() - n, getY() + n)->getColor() == getColor()))
            break;
        if (j == getX() - n && i == getY() + n)
        {
            return true;
        }
    }
    for (int n = 1; n < 8; n++) // diagonale sud-est
    {
        if ((sca.getPedina(getX() + n, getY() + n)->getName() != 'e') && (sca.getPedina(getX() + n, getY() + n)->getColor() == getColor()))
            break;
        if (j == getX() + n && i == getY() + n)
        {
            return true;
        }
    }
    for (int n = 1; n < 8; n++) // diagonale nord-est
    {
        if ((sca.getPedina(getX() + n, getY() - n)->getName() != 'e') && (sca.getPedina(getX() + n, getY() - n)->getColor() == getColor()))
            break;
        if (j == getX() + n && i == getY() - n)
        {
            return true;
        }
    }
    return false;
}

//_______________________________________TORRE___________________________________________
bool Torre::move(int px, int py, Scacchiera &sca)
{
    return false;
}

bool Torre::checkPos(int j, int i, Scacchiera &sca)
{
    sca.checkBoundaries(j, i);
    for (int n = 1; n < 8; n++) // sinistra
    {
        if (i != getY()) // se riga diversa non puo' essere a sx o dx
            break;
        if ((sca.getPedina(getX() - n, i)->getName() != 'e') && (sca.getPedina(getX() - n, i)->getColor() == getColor()))
            break;
        if (j == getX() - n)
        {
            return true;
        }
    }
    for (int n = 1; n < 8; n++) // destra
    {
        if (i != getY())
            break;
        if ((sca.getPedina(getX() + n, i)->getName() != 'e') && (sca.getPedina(getX() + n, i)->getColor() == getColor()))
            break;
        if (j == getX() + n)
        {
            return true;
        }
    }
    for (int n = 1; n < 8; n++) // su
    {
        if (j != getX()) // se colonna diversa non puo' essere su o giu
            break;
        if ((sca.getPedina(j, getY() - n)->getName() != 'e') && (sca.getPedina(j, getY() - n)->getColor() == getColor()))
            break;
        if (i == getY() - n)
        {
            return true;
        }
    }
    for (int n = 1; n < 8; n++) // giu
    {
        if (j != getX())
            break;
        if ((sca.getPedina(j, getY() + n)->getName() != 'e') && (sca.getPedina(j, getY() + n)->getColor() == getColor()))
            break;
        if (i == getY() + n)
        {
            return true;
        }
    }
    return false;
}

//_______________________________________RE___________________________________________
bool Re::move(int px, int py, Scacchiera &sca)
{
    return false;
}

bool Re::checkPos(int j, int i, Scacchiera &sca)
{
    sca.checkBoundaries(j, i);
    if (j == getX() && (i == getY() - 1 || i == getY() + 1))
    {
        if ((sca.getPedina(j, i)->getName() != 'e') && (sca.getPedina(j, i)->getColor() == getColor()))
            return false;
        return true;
    }
    else if (j == getX() - 1 && (i == getY() || i == getY() - 1 || i == getY() + 1))
    {
        if (((*sca.getPedina(j, i)).getName() != 'e') && ((*sca.getPedina(j, i)).getColor() == getColor()))
            return false;
        return true;
    }
    else if (j == getX() + 1 && (i == getY() || i == getY() - 1 || i == getY() + 1))
    {
        if (((*sca.getPedina(j, i)).getName() != 'e') && ((*sca.getPedina(j, i)).getColor() == getColor()))
            return false;
        return true;
    }
    return false;
}

//_______________________________________REGINA___________________________________________
bool Regina::move(int px, int py, Scacchiera &sca)
{
    return false;
}

bool Regina::checkPos(int j, int i, Scacchiera &sca)
{
    sca.checkBoundaries(j, i);
    for (int n = 1; n < 8; n++) // sinistra
    {
        if (i != getY()) // se riga diversa non puo' essere a sx o dx
            break;
        if (((*sca.getPedina(getX() - n, i)).getName() != 'e') && ((*sca.getPedina(getX() - n, i)).getColor() == getColor()))
            break;
        if (j == getX() - n)
        {
            return true;
        }
    }
    for (int n = 1; n < 8; n++) // destra
    {
        if (i != getY())
            break;
        if (((*sca.getPedina(getX() + n, i)).getName() != 'e') && ((*sca.getPedina(getX() + n, i)).getColor() == getColor()))
            break;
        if (j == getX() + n)
        {
            return true;
        }
    }
    for (int n = 1; n < 8; n++) // su
    {
        if (j != getX()) // se colonna diversa non puo' essere su o giu
            break;
        if (((*sca.getPedina(j, getY() - n)).getName() != 'e') && ((*sca.getPedina(j, getY() - n)).getColor() == getColor()))
            break;
        if (i == getY() - n)
        {
            return true;
        }
    }
    for (int n = 1; n < 8; n++) // giu
    {
        if (j != getX())
            break;
        if (((*sca.getPedina(j, getY() + n)).getName() != 'e') && ((*sca.getPedina(j, getY() + n)).getColor() == getColor()))
            break;
        if (i == getY() + n)
        {
            return true;
        }
    }
    for (int n = 1; n < 8; n++) // diagonale nord-ovest
    {
        if (((*sca.getPedina(getX() - n, getY() - n)).getName() != 'e') && ((*sca.getPedina(getX() - n, getY() - n)).getColor() == getColor()))
            break;
        if (j == getX() - n && i == getY() - n)
        {
            return true;
        }
    }
    for (int n = 1; n < 8; n++) // diagonale sud-ovest
    {
        if (((*sca.getPedina(getX() - n, getY() + n)).getName() != 'e') && ((*sca.getPedina(getX() - n, getY() + n)).getColor() == getColor()))
            break;
        if (j == getX() - n && i == getY() + n)
        {
            return true;
        }
    }
    for (int n = 1; n < 8; n++) // diagonale sud-est
    {
        if (((*sca.getPedina(getX() + n, getY() + n)).getName() != 'e') && ((*sca.getPedina(getX() + n, getY() + n)).getColor() == getColor()))
            break;
        if (j == getX() + n && i == getY() + n)
        {
            return true;
        }
    }
    for (int n = 1; n < 8; n++) // diagonale nord-est
    {
        if (((*sca.getPedina(getX() + n, getY() - n)).getName() != 'e') && ((*sca.getPedina(getX() + n, getY() - n)).getColor() == getColor()))
            break;
        if (j == getX() + n && i == getY() - n)
        {
            return true;
        }
    }
    return false;
}
