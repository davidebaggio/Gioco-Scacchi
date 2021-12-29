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
bool Pedone::checkPos(int, int) 
{
    return false;
}

bool Pedone::checkCattura(int, int)
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

bool Cavallo::checkPos(int, int)
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

bool Alfiere::checkPos(int, int) 
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

bool Torre::checkPos(int, int) 
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

bool Re::checkPos(int, int) 
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

bool Regina::checkPos(int, int) 
{
    return false;
}


ostream &operator<<(ostream &os, const Regina &d)
{
    os << d.getName();
    return os;
}

//_______________________________________EMPTY___________________________________________

ostream &operator<<(ostream &os, const Empty &e)
{
    os << e.getName();
    return os;
}

bool Empty::move(int, int)
{
    return false;
}
bool Empty::checkPos(int, int)
{
    return false;
}
