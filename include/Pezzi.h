// Melissa Maistro
/*
    operator << di tutte le pedine sono inutili (?) perché c'è quello di pedina
*/

#ifndef PEZZI_H
#define PEZZI_H
#include "Scacchiera.h"

//_______________________________________PEDONE___________________________________________
class Pedone : public Pedina
{
public:
    Pedone() : Pedina() {}
    Pedone(int l, int n, bool color, char na) : Pedina(l, n, color, na) {}
    bool move(int, int, Scacchiera &) override;
    bool checkPos(int, int, Scacchiera &) override;
};
//_______________________________________CAVALLO___________________________________________
class Cavallo : public Pedina
{
public:
    Cavallo() : Pedina() {}
    Cavallo(int l, int n, bool color, char na) : Pedina(l, n, color, na) {}
    bool move(int, int, Scacchiera &) override;
    bool checkPos(int, int, Scacchiera &) override;
};
//_______________________________________ALFIERE___________________________________________
class Alfiere : public Pedina
{
public:
    Alfiere() : Pedina() {}
    Alfiere(int l, int n, bool color, char na) : Pedina(l, n, color, na) {}
    bool move(int, int, Scacchiera &) override;
    bool checkPos(int, int, Scacchiera &) override;
};
//_______________________________________TORRE___________________________________________
class Torre : public Pedina
{
public:
    Torre() : Pedina() {}
    Torre(int l, int n, bool color, char na) : Pedina(l, n, color, na) {}
    bool move(int, int, Scacchiera &) override;
    bool checkPos(int, int, Scacchiera &) override;
};
//_______________________________________RE___________________________________________
class Re : public Pedina
{
public:
    Re() : Pedina() {}
    Re(int l, int n, bool color, char na) : Pedina(l, n, color, na) {}
    bool move(int, int, Scacchiera &) override;
    bool checkPos(int, int, Scacchiera &) override;
};
//_______________________________________REGINA___________________________________________
class Regina : public Pedina
{
public:
    Regina() : Pedina() {}
    Regina(int l, int n, bool color, char na) : Pedina(l, n, color, na) {}
    bool move(int, int, Scacchiera &) override;
    bool checkPos(int, int, Scacchiera &) override;
};

#endif