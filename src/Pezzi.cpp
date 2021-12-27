// Melissa Maistro

#include "../include/Pezzi.h"
#include "../include/Scacchiera.h"
#include <iostream>
using namespace std;

//_______________________________________PEDONE___________________________________________
bool Pedone::move(int px, int py)
{
    return false;
}
bool Pedone::checkPos()
{
    return false;
}

ostream &operator<<(ostream &os, const Pedone &p)
{
    os << p.getName();
    return os;
}

//_______________________________________CAVALLO___________________________________________
bool Cavallo::move(int px, int py)
{
    return false;
}
bool Cavallo::checkPos()
{
    return false;
}

ostream &operator<<(ostream &os, const Cavallo &c)
{
    os << c.getName();
    return os;
}

//_______________________________________ALFIERE___________________________________________
bool Alfiere::move(int px, int py)
{
    return false;
}
bool Alfiere::checkPos()
{
    return false;
}

ostream &operator<<(ostream &os, const Alfiere &a)
{
    os << a.getName();
    return os;
}

//_______________________________________TORRE___________________________________________
bool Torre::move(int px, int py)
{
    return false;
}
bool Torre::checkPos()
{
    return false;
}

ostream &operator<<(ostream &os, const Torre &t)
{
    os << t.getName();
    return os;
}

//_______________________________________RE___________________________________________
bool Re::move(int px, int py)
{
    return false;
}
bool Re::checkPos()
{
    return false;
}

ostream &operator<<(ostream &os, const Re &r)
{
    os << r.getName();
    return os;
}

//_______________________________________REGINA___________________________________________
bool Regina::move(int px, int py)
{
    return false;
}
bool Regina::checkPos()
{
    return false;
}

ostream &operator<<(ostream &os, const Regina &d)
{
    os << d.getName();
    return os;
}

//_______________________________________EMPTY___________________________________________
bool Empty::move(int px, int py)
{
    return false;
}
bool Empty::checkPos()
{
    return false;
}

ostream &operator<<(ostream &os, const Empty &e)
{
    os << e.getName();
    return os;
}