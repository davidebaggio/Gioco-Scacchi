//Melissa Maistro

#include "../include/Pezzi.h"
#include "../include/Scacchiera.h"
#include <iostream>
using namespace std;

//_______________________________________PEDONE___________________________________________
bool Pedone::move(int, int) 
{
    return false;
}
bool Pedone::checkPos() 
{
    return false;
}

ostream& Pedone::operator<< (ostream& os)
{
    if(getColor())
        os << "p";
    else
        os << "P";
}
//_______________________________________CAVALLO___________________________________________
bool Cavallo::move(int, int) 
{
    return false;
}
bool Cavallo::checkPos() 
{
    return false;
}

ostream& Cavallo::operator<< (ostream& os)
{
    if(getColor())
        os << "c";
    else
        os << "C";
}
//_______________________________________ALFIERE___________________________________________
bool Alfiere::move(int, int) 
{
    return false;
}
bool Alfiere::checkPos() 
{
    return false;
}

ostream& Alfiere::operator<< (ostream& os)
{
    if(getColor())
        os << "a";
    else
        os << "A";
}
//_______________________________________TORRE___________________________________________
bool Torre::move(int, int) 
{
    return false;
}
bool Torre::checkPos() 
{
    return false;
}

ostream& Torre::operator<< (ostream& os)
{
    if(getColor())
        os << "t";
    else
        os << "T";
}
//_______________________________________RE___________________________________________
bool Re::move(int, int) 
{
    return false;
}
bool Re::checkPos() 
{
    return false;
}

ostream& Re::operator<< (ostream& os)
{
    if(getColor())
        os << "r";
    else
        os << "R";
}
//_______________________________________REGINA___________________________________________
bool Regina::move(int, int) 
{
    return false;
}
bool Regina::checkPos() 
{
    return false;
}

ostream& Regina::operator<< (ostream& os)
{
    if(getColor())
        os << "d";
    else
        os << "D";
}