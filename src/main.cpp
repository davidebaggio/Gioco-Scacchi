#include <iostream>
#include "../include/Scacchiera.h"
#include "../include/Pezzi.h"

using namespace std;

int main()
{
    Scacchiera s = Scacchiera();
    cout << s;

    cout<<endl;
    cout << s.getPedina(1, 1) << endl;

    Pedina p = Torre(1, 1, false, 't');
    s.setPedina(p);
    cout << s;

    if(s.isScacco())
        cout << "SCACCO!";
    else
        cout << "non scacco";
    return 0;
}