#include <iostream>
#include <string.h>
#include "../include/Scacchiera.h"
#include "../include/Pezzi.h"

using namespace std;

int main(int argc, char *argv[])
{
    if (argc <= 1)
    {
        cout << "[Error] Not enough arguments. Type: " << endl
             << "\t -pc: to play vs computer." << endl
             << "\t -cc: to watch a match computer vs computer." << endl;
        return 0;
    }
    else if (_strcmpi(argv[1], "-pc") != 0 && _strcmpi(argv[1], "-cc") != 0)
    {
        cout << "[Error] Incorrect arguments. Type: " << endl
             << "\t -pc: to play vs computer." << endl
             << "\t -cc: to watch a match computer vs computer." << endl;
        return 0;
    }
    else if (_strcmpi(argv[1], "-pc") == 0)
    {
        cout << "Partita giocatore vs computer\n";
        Scacchiera s = Scacchiera();
        cout << "Scacchiera iniziale: \n"
             << s << "\n";
        return 0;
    }
    else
    {
        cout << "Partita computer vs computer\n";
        Scacchiera s = Scacchiera();
        cout << "Scacchiera iniziale: \n"
             << s << "\n";
        int mosseMax = 30;
        return 0;
    }
    /*
    cout<<endl;
    cout << s.getPedina(1, 1) << endl;

    Pedina p = Torre(1, 1, false, 't');
    s.setPedina(p);
    cout << s;

    if(s.isScacco())
        cout << "SCACCO!";
    else
        cout << "non scacco"; */
}