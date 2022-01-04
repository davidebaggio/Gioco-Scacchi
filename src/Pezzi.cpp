// Melissa Maistro

#include "../include/Pezzi.h"
#include "../include/Scacchiera.h"
#include <iostream>
using namespace std;

//_______________________________________PEDONE___________________________________________

bool Pedone::checkPos(int j, int i, Pedina *matrice[8][8]) // controlla se puo' muoversi nella posizione data
{
    if (getColor()) // se bianco
    {
        if (j == getX() && (i == getY() - 1)) // se avanti di 1
        {
            if (!emptyBox(matrice, j, i)) // se c'e' una pedina non puo'
                return false;
            return true;
        }
        if (isFirstMove() && j == getX() && i == getY() - 2) // se prima mossa e avanti di 2
        {
            if (!emptyBox(matrice, j, i) || !emptyBox(matrice, j, getY() - 1))
                return false; // se c'e' una pedina nella prima o seconda cella non puo'
            return true;
        }
        if ((i == getY() - 1 && (j == getX() - 1 || j == getX() + 1))) // se nelle due celle diagonali
        {
            if (!emptyBox(matrice, j, i) && !(matrice[j][i]->getColor())) // solo se c'e' una pedina nera
                return true;
            return false;
        }
    }
    // se nero
    {
        if (j == getX() && (i == getY() + 1)) // se avanti di 1
        {
            if (!emptyBox(matrice, j, i)) // se c'e' una pedina non puo'
                return false;
            return true;
        }
        if (isFirstMove() && j == getX() && i == getY() + 2) // se prima mossa e avanti di 2
        {
            if (!emptyBox(matrice, j, i) || !emptyBox(matrice, j, getY() + 1))
                return false; // se c'e' una pedina nella prima o seconda cella non puo'
            return true;
        }
        if ((i == getY() + 1 && (j == getX() - 1 || j == getX() + 1))) // se nelle due celle diagonali
        {
            if (!emptyBox(matrice, j, i) && matrice[j][i]->getColor()) // solo se c'e' una pedina bianca
                return true;
            return false;
        }
    }
    return false; // ritorna false se non puo' spostarsi nella casella
}

//_______________________________________CAVALLO___________________________________________

bool Cavallo::checkPos(int j, int i, Pedina *matrice[8][8]) // si sposta a L in tutte le direzioni anche se ci sono pedine
{                                                           // j colonne, i righe
    if (j == getX() && (i == getY() - 1 || i == getY() - 2 || i == getY() + 1 || i == getY() + 2))
        return true;
    if (j == getX() - 1 && (i == getY() || i == getY() - 1 || i == getY() - 2 || i == getY() + 1 || i == getY() + 2))
        return true;
    if (j == getX() - 2 && (i == getY() || i == getY() - 1 || i == getY() + 1))
        return true;
    if (j == getX() + 1 && (i == getY() || i == getY() - 1 || i == getY() - 2 || i == getY() + 1 || i == getY() + 2))
        return true;
    if (j == getX() + 2 && (i == getY() || i == getY() - 1 || i == getY() + 1))
        return true;
    return false;
}

//_______________________________________ALFIERE___________________________________________

bool Alfiere::checkPos(int j, int i, Pedina *matrice[8][8]) // si muove nelle 4 diagonali
{
    for (int n = 1; n < 8; n++) // diagonale nord-ovest
    {
        if (!checkBoundaries(getX() - n, getY() - n))
            break;
        if (!emptyBox(matrice, getX() - n, getY() - n) && matrice[getX() - n][getY() - n]->getColor() == getColor())
            break; // se c'e' una pedina ed e' del suo colore non va oltre
        if (j == getX() - n && i == getY() - n)
            return true;
    }
    for (int n = 1; n < 8; n++) // diagonale sud-ovest
    {
        if (!checkBoundaries(getX() - n, getY() + n))
            break;
        if (!emptyBox(matrice, getX() - n, getY() + n) && (matrice[getX() - n][getY() + n]->getColor() == getColor()))
            break;
        if (j == getX() - n && i == getY() + n)
            return true;
    }
    for (int n = 1; n < 8; n++) // diagonale sud-est
    {
        if (!checkBoundaries(getX() + n, getY() + n))
            break;
        if (!emptyBox(matrice, getX() + n, getY() + n) && (matrice[getX() + n][getY() + n]->getColor() == getColor()))
            break;
        if (j == getX() + n && i == getY() + n)
            return true;
    }
    for (int n = 1; n < 8; n++) // diagonale nord-est
    {
        if (!checkBoundaries(getX() + n, getY() - n))
            break;
        if (!emptyBox(matrice, getX() + n, getY() - n) && (matrice[getX() + n][getY() - n]->getColor() == getColor()))
            break;
        if (j == getX() + n && i == getY() - n)
            return true;
    }
    return false;
}

//_______________________________________TORRE___________________________________________

bool Torre::checkPos(int j, int i, Pedina *matrice[8][8])
{
    for (int n = 1; n < 8; n++) // sinistra
    {
        if (i != getY()) // se riga diversa non puo' essere a sx o dx
            break;
        if (!checkBoundaries(getX() - n, getY()))
            break;
        if (!emptyBox(matrice, getX() - n, i) && (matrice[getX() - n][i]->getColor() == getColor()))
            break;
        if (j == getX() - n)
            return true;
    }
    for (int n = 1; n < 8; n++) // destra
    {
        if (i != getY())
            break;
        if (!checkBoundaries(getX() + n, getY()))
            break;
        if (!emptyBox(matrice, getX() + n, i) && (matrice[getX() + n][i]->getColor() == getColor()))
            break;
        if (j == getX() + n)
            return true;
    }
    for (int n = 1; n < 8; n++) // su
    {
        if (j != getX()) // se colonna diversa non puo' essere su o giu
            break;
        if (!checkBoundaries(getX(), getY() - n))
            break;
        if (!emptyBox(matrice, j, getY() - n) && (matrice[j][getY() - n]->getColor() == getColor()))
            break;
        if (i == getY() - n)
            return true;
    }
    for (int n = 1; n < 8; n++) // giu
    {
        if (j != getX())
            break;
        if (!checkBoundaries(getX(), getY() + n))
            break;
        if (!emptyBox(matrice, j, getY() + n) && (matrice[j][getY() + n]->getColor() == getColor()))
            break;
        if (i == getY() + n)
            return true;
    }
    return false;
}

//_______________________________________RE___________________________________________

bool Re::checkPos(int j, int i, Pedina *matrice[8][8])
{
    if (j == getX() && (i == getY() - 1 || i == getY() + 1))
    {
        if (!emptyBox(matrice, j, i) && (matrice[j][i]->getColor() == getColor()))
            return false;
        return true;
    }
    if (j == getX() - 1 && (i == getY() || i == getY() - 1 || i == getY() + 1))
    {
        if (!emptyBox(matrice, j, i) && (matrice[j][i]->getColor() == getColor()))
            return false;
        return true;
    }
    if (j == getX() + 1 && (i == getY() || i == getY() - 1 || i == getY() + 1))
    {
        if (!emptyBox(matrice, j, i) && (matrice[j][i]->getColor() == getColor()))
            return false;
        return true;
    }
    return false;
}

// //_______________________________________REGINA___________________________________________

bool Regina::checkPos(int j, int i, Pedina *matrice[8][8])
{
    for (int n = 1; n < 8; n++) // sinistra
    {
        if (i != getY()) // se riga diversa non puo' essere a sx o dx
            break;
        if (!checkBoundaries(getX() - n, getY()))
            break;
        if (!emptyBox(matrice, getX() - n, i) && (matrice[getX() - n][i]->getColor() == getColor()))
            break;
        if (j == getX() - n)
            return true;
    }
    for (int n = 1; n < 8; n++) // destra
    {
        if (i != getY())
            break;
        if (!checkBoundaries(getX() + n, getY()))
            break;
        if (!emptyBox(matrice, getX() + n, i) && (matrice[getX() + n][i]->getColor() == getColor()))
            break;
        if (j == getX() + n)
            return true;
    }
    for (int n = 1; n < 8; n++) // su
    {
        if (j != getX()) // se colonna diversa non puo' essere su o giu
            break;
        if (!checkBoundaries(getX(), getY() - n))
            break;
        if (!emptyBox(matrice, j, getY() - n) && (matrice[j][getY() - n]->getColor() == getColor()))
            break;
        if (i == getY() - n)
            return true;
    }
    for (int n = 1; n < 8; n++) // giu
    {
        if (j != getX())
            break;
        if (!checkBoundaries(getX(), getY() + n))
            break;
        if (!emptyBox(matrice, j, getY() + n) && (matrice[j][getY() + n]->getColor() == getColor()))
            break;
        if (i == getY() + n)
            return true;
    }
    for (int n = 1; n < 8; n++) // diagonale nord-ovest
    {
        if (!checkBoundaries(getX() - n, getY() - n))
            break;
        if (!emptyBox(matrice, getX() - n, getY() - n) && (matrice[getX() - n][getY() - n]->getColor() == getColor()))
            break; // se c'e' una pedina ed e' del suo colore non va oltre
        if (j == getX() - n && i == getY() - n)
            return true;
    }
    for (int n = 1; n < 8; n++) // diagonale sud-ovest
    {
        if (!checkBoundaries(getX() - n, getY() + n))
            break;
        if (!emptyBox(matrice, getX() - n, getY() + n) && (matrice[getX() - n][getY() + n]->getColor() == getColor()))
            break;
        if (j == getX() - n && i == getY() + n)
            return true;
    }
    for (int n = 1; n < 8; n++) // diagonale sud-est
    {
        if (!checkBoundaries(getX() + n, getY() + n))
            break;
        if (!emptyBox(matrice, getX() + n, getY() + n) && (matrice[getX() + n][getY() + n]->getColor() == getColor()))
            break;
        if (j == getX() + n && i == getY() + n)
            return true;
    }
    for (int n = 1; n < 8; n++) // diagonale nord-est
    {
        if (!checkBoundaries(getX() + n, getY() - n))
            break;
        if (!emptyBox(matrice, getX() + n, getY() - n) && (matrice[getX() + n][getY() - n]->getColor() == getColor()))
            break;
        if (j == getX() + n && i == getY() - n)
            return true;
    }
    return false;
}

//-------------------------------------------- HELPER FUNCTIONS --------------------------------------------

bool checkBoundaries(int j, int i)
{
    return (i >= 0 || i <= 7 || j >= 0 || j <= 7);
}

bool emptyBox(Pedina *matrice[8][8], int x, int y)
{
    return matrice[x][y] == nullptr;
}