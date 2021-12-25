// Melissa Maistro

#ifndef PEZZI_H
#define PEZZI_H
#include "Scacchiera.h"

//_______________________________________PEDONE___________________________________________
class Pedone : public Pedina
{
public:
    Pedone(int l, int n, bool color, char na) : Pedina(l, n, color, na) {}
    bool move(int, int) override;
    bool checkPos() override;
};
//_______________________________________CAVALLO___________________________________________
class Cavallo : public Pedina
{
public:
    Cavallo(int l, int n, bool color, char na) : Pedina(l, n, color, na) {}
    bool move(int, int) override;
    bool checkPos() override;
};
//_______________________________________ALFIERE___________________________________________
class Alfiere : public Pedina
{
public:
    Alfiere(int l, int n, bool color, char na) : Pedina(l, n, color, na) {}
    bool move(int, int) override;
    bool checkPos() override;
};
//_______________________________________TORRE___________________________________________
class Torre : public Pedina
{
public:
    Torre(int l, int n, bool color, char na) : Pedina(l, n, color, na) {}
    bool move(int, int) override;
    bool checkPos() override;
};
//_______________________________________RE___________________________________________
class Re : public Pedina
{
public:
    Re(int l, int n, bool color, char na) : Pedina(l, n, color, na) {}
    bool move(int, int) override;
    bool checkPos() override;
};
//_______________________________________REGINA___________________________________________
class Regina : public Pedina
{
public:
    Regina(int l, int n, bool color, char na) : Pedina(l, n, color, na) {}
    bool move(int, int) override;
    bool checkPos() override;
};

#endif