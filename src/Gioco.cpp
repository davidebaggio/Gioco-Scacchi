// Baggio Davide
#include <iostream>
#include <fstream>
#include <string.h>
#include <chrono>
#include <thread>
#include <cstdlib>
#include <time.h>
#include <sstream>
#include "../include/Scacchiera.h"

using namespace std;

bool isValid(const string &cmd) // funzione che controlla se il comando inserito è formattato in modo corretto
{
    if (cmd.length() != 5 || (int)cmd[0] < 65 || (int)cmd[0] > 72 || (int)cmd[1] < 49 || (int)cmd[1] > 57 ||
        (int)cmd[3] < 65 || (int)cmd[3] > 72 || (int)cmd[4] < 49 || (int)cmd[4] > 57 || cmd[2] != ' ')
    {
        cout << "Errore nella scrittura del comando\n";
        return false;
    }

    else
        return true;
}

bool computeCommand(Scacchiera &sca, const string &cmd, bool col, bool err) // funzione che trasforma il comado 'stringa' in coordinate di partenza e arrivo della pedina
{
    if (!isValid(cmd))
        return false;
    int xi = ((int)cmd[0]) - 65; //-65 per ascii table A
    int yi = ((int)cmd[1]) - 49; //-49 per ascii table 1
    int xf = ((int)cmd[3]) - 65; //-65 per ascii table A
    int yf = ((int)cmd[4]) - 49; //-49 per ascii table 1
    Pedina *temp = sca.getPedina(xi, yi);
    if (temp == nullptr)
    {
        if (err)
            cout << "Non stai spostando alcuna pedina\n";
        // delete temp;
        return false;
    }
    if (temp->getColor() != col)
    {
        if (err)
            cout << "Stai spostando la pedina dell'altro colore.\n";
        // delete temp;
        return false;
    }
    try
    {
        sca.move(temp, xf, yf);
    }
    catch (const InvalidPosition &e)
    {
        if (err)
            cout << "Mossa non consentita.\n";
        // delete temp;
        return false;
    }
    // delete temp;
    return true;
}

int main(int argc, char *argv[])
{
    srand(time(NULL));
    // using namespace std::this_thread; // sleep_for
    using namespace std::chrono; // seconds
    // if (argc <= 1)
    if (false)
    {
        cout << "[Error] Not enough arguments. Type: " << endl
             << "\t -pc: to play vs computer." << endl
             << "\t -cc: to watch a match computer vs computer." << endl;
        return 0;
    }

    // else if (strcmp(argv[1], "-pc") != 0 && strcmp(argv[1], "-cc") != 0) //<----------------------------------------------------
    else if (false)
    {
        cout << "[Error] Incorrect arguments. Type: " << endl
             << "\t -pc: to play vs computer." << endl
             << "\t -cc: to watch a match computer vs computer." << endl;
        return 0;
    }
    // else if (strcmp(argv[1], "-pc") == 0) //<----------------------------------------------------
    else if (true)
    {
        cout << "Partita giocatore (Bianco) vs computer (Nero)\n";
        cout << "Per giocare inserire la posizione di cella iniziale e finale separati da uno spazio. Es: A2 C3\n";
        Scacchiera s{};
        cout << "Scacchiera iniziale: \n"
             << "\n"
             << s << "\n";
        ofstream outputFile("output.txt");
        outputFile.clear();
        while (!s.isScacco() && !s.isPatta() && !s.isScaccoMatto())
        {
            // player
            cout << "player: \n";
            string commandPL;
            do
            {
                getline(cin, commandPL);
            } while (!computeCommand(s, commandPL, true, true));
            cout << "\n"
                 << s << "\n";
            outputFile << commandPL << "\n";

            // sleep_for(seconds(1)); // 1 secondo da una giocata all'altra

            // computer
            cout << "computer: \n";
            string commandPC = "";
            do
            {
                char c1;
                commandPC = "";
                for (int i = 0; i < 5; i++)
                {
                    if (i == 0 || i == 3)
                        c1 = (char)(rand() % 8 + 65);
                    else
                        c1 = (char)(rand() % 8 + 49);
                    if (i != 2)
                        commandPC += c1;
                    else
                        commandPC += " ";
                }
                // cout << commandPC << "\n";
            } while (!computeCommand(s, commandPC, false, false));
            cout << commandPC << "\n"
                 << s << "\n";
            outputFile << commandPC << "\n";
        }
        outputFile.close();
        return 0;
    }
    else
    {
        cout << "Partita computer vs computer\n";
        Scacchiera s{};
        cout << "Scacchiera iniziale: \n"
             << "\n"
             << s << "\n";
        int mosseMax = 30;
        ofstream outputFile("output.txt");
        outputFile.clear();
        while (!s.isScacco() && !s.isPatta() && !s.isScaccoMatto() && mosseMax > 0)
        {
            cout << "computer 1: \n";
            string commandPC1 = "";
            do
            {
                char c1;
                commandPC1 = "";
                for (int i = 0; i < 5; i++)
                {
                    if (i == 0 || i == 3)
                        c1 = (char)(rand() % 8 + 65);
                    else
                        c1 = (char)(rand() % 8 + 49);
                    if (i != 2)
                        commandPC1 += c1;
                    else
                        commandPC1 += " ";
                }
                // cout << commandPC1 << "\n";
            } while (!computeCommand(s, commandPC1, true, false));
            cout << commandPC1 << "\n"
                 << s << "\n";
            outputFile << commandPC1 << "\n";

            // sleep_for(seconds(1)); // 1 secondo da una giocata all'altra

            cout << "computer 2: \n";
            string commandPC2 = "";
            do
            {
                char c1;
                commandPC2 = "";
                for (int i = 0; i < 5; i++)
                {
                    if (i == 0 || i == 3)
                        c1 = (char)(rand() % 8 + 65);
                    else
                        c1 = (char)(rand() % 8 + 49);
                    if (i != 2)
                        commandPC2 += to_string(c1);
                    else
                        commandPC2 += " ";
                }
                // cout << commandPC2 << "\n";
            } while (!computeCommand(s, commandPC2, false, false));
            cout << commandPC2 << "\n"
                 << s << "\n";
            outputFile << commandPC2 << "\n";
            mosseMax--;
        }
        return 0;
    }
}

int main2()
{
    Scacchiera s{};
    cout << "Scacchiera iniziale: \n";
    cout << s << "\n";

    Pedina *cavallo = s.getPedina(1, 0);
    Pedina *ped1 = s.getPedina(5, 6);
    Pedina *ped2 = s.getPedina(1, 6);
    Pedina *torre = s.getPedina(0, 7);
    Pedina *alfiere = s.getPedina(2, 7);
    Pedina *regina = s.getPedina(3, 7);
    Pedina *re = s.getPedina(4, 7);

    s.move(cavallo, 2, 2);
    s.move(ped1, 5, 5);
    s.move(ped2, 1, 4);

    /* if (!s.move(cavallo, 1, 4))
        cout << "mangiato!!" << endl; */

    s.move((s.getPedina(0, 6)), 0, 5);
    s.move((s.getPedina(0, 5)), 1, 4);

    s.move(torre, 0, 1);
    s.move(alfiere, 0, 5);
    s.move(regina, 2, 7);
    s.move(re, 5, 6);

    //    Pedina* pp = s.getPedina(7,5);
    //    cout << "posizione 7,5:" <<pp->getName() <<endl;
    cout << s;

    return 0;
}