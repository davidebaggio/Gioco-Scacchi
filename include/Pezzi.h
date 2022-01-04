// Melissa Maistro
/*
    operator << di tutte le pedine sono inutili (?) perche' c'e' quello di pedina
*/

#ifndef PEZZI_H
#define PEZZI_H
#include "Scacchiera.h"

//_______________________________________PEDONE___________________________________________
class Pedone : public Pedina
{
public:
    // Pedone() : Pedina() {}
    Pedone(int l, int n, bool color, char na) : Pedina(l, n, color, na) {}
    virtual ~Pedone() {}
    // bool move(int, int, Scacchiera &) override;
    bool checkPos(int destX, int destY, Pedina *matrice[8][8]) override;
};
//_______________________________________CAVALLO___________________________________________
class Cavallo : public Pedina
{
public:
    // Cavallo() : Pedina() {}
    Cavallo(int l, int n, bool color, char na) : Pedina(l, n, color, na) {}
    virtual ~Cavallo() {}
    // bool move(int, int, Scacchiera &) override;
    bool checkPos(int destX, int destY, Pedina *matrice[8][8]) override;
};
//_______________________________________ALFIERE___________________________________________
class Alfiere : public Pedina
{
public:
    // Alfiere() : Pedina() {}
    Alfiere(int l, int n, bool color, char na) : Pedina(l, n, color, na) {}
    virtual ~Alfiere() {}
    // bool move(int, int, Scacchiera &) override;
    bool checkPos(int destX, int destY, Pedina *matrice[8][8]) override;
};
//_______________________________________TORRE___________________________________________
class Torre : public Pedina
{
public:
    // Torre() : Pedina() {}
    Torre(int l, int n, bool color, char na) : Pedina(l, n, color, na) {}
    virtual ~Torre() {}
    // bool move(int, int, Scacchiera &) override;
    bool checkPos(int destX, int destY, Pedina *matrice[8][8]) override;
};
//_______________________________________RE___________________________________________
class Re : public Pedina
{
public:
    // Re() : Pedina() {}
    Re(int l, int n, bool color, char na) : Pedina(l, n, color, na) {}
    virtual ~Re() {}
    // bool move(int, int, Scacchiera &) override;
    bool checkPos(int destX, int destY, Pedina *matrice[8][8]) override;
};
//_______________________________________REGINA___________________________________________
class Regina : public Pedina
{
public:
    // Regina() : Pedina() {}
    Regina(int l, int n, bool color, char na) : Pedina(l, n, color, na) {}
    virtual ~Regina() {}
    // bool move(int, int, Scacchiera &) override;
    bool checkPos(int destX, int destY, Pedina *matrice[8][8]) override;
};

// HELPER FUNCTION
bool checkBoundaries(int i, int j);
bool emptyBox(Pedina *matrice[8][8], int x, int y);

#endif