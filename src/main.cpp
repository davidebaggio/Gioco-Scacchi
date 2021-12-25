#include <iostream>
#include "../include/Scacchiera.h"
#include "../include/Pezzi.h"

using namespace std;

int main()
{
    Scacchiera s = Scacchiera();
    cout << s.getPedina(0, 0);
    return 0;
}