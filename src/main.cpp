#include <iostream>
#include "../include/Scacchiera.h"
#include "../include/Pezzi.h"

using namespace std;

int main()
{
    Scacchiera s = Scacchiera();
    cout << s;
    Pedina p = Torre(1, 1, false, 't');
    cout << p;
    return 0;
}