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
#include "../include/Pezzi.h"

using namespace std;

bool isValid(const string &cmd)
{
    if (cmd.length() != 5 || (int)cmd[0] < 65 || (int)cmd[0] > 72 || cmd[1] < 1 || cmd[1] > 8 ||
        (int)cmd[3] < 65 || (int)cmd[3] > 72 || cmd[4] < 1 || cmd[4] > 8 || cmd[2] != ' ')
        return false;
    else
        return true;
}

bool computeCommand(Scacchiera &sca, const string &cmd, bool col)
{
    if (!isValid(cmd))
        return false;
    int xi = ((int)cmd[0]) - 65; //-65 per ascii table A
    int yi = ((int)cmd[1]) - 49; //-49 per ascii table 1
    int xf = ((int)cmd[3]) - 65; //-65 per ascii table B
    int yf = ((int)cmd[4]) - 49; //-49 per ascii table 3
    Pedina &temp = sca.getPedina(xi, yi);
    if (temp.getColor() != col)
        return false;
    try
    {
        temp.move(xf, yf, sca);
    }
    catch (const Pedina::InvalidPosition &e)
    {
        return false;
    }
    return true;
}

int main(int argc, char *argv[])
{
    srand(time(NULL));
    using namespace std::this_thread; // sleep_for
    using namespace std::chrono;      // seconds
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
        cout << "Partita giocatore (Bianco) vs computer(Nero)\n";
        cout << "Per giocare inserire la posizione di cella iniziale e finale\nEs: A2 C3";
        Scacchiera s = Scacchiera();
        cout << "Scacchiera iniziale: \n"
             << s << "\n";
        ofstream outputFile("output.txt");
        outputFile.clear();
        while (!s.isScacco() && !s.isPatta() && !s.isScaccoMatto())
        {
            // player
            cout << "player: ";
            string commandPL;
            do
            {
                cin >> commandPL;
                if (!isValid(commandPL))
                    cout << "[Error] Spostamento non valido\n";
            } while (!computeCommand(s, commandPL, true));
            cout << s;
            outputFile << commandPL << "\n";

            sleep_for(seconds(1)); // 1 secondo da una giocata all'altra

            // computer
            cout << "computer: ";
            string commandPC = "";
            do
            {
                int c1[5];
                commandPC = "";
                for (int i = 0; i < 5; i++)
                {
                    c1[i] = rand() % 8;
                    if (i != 2)
                        commandPC += to_string(c1[i]);
                    else
                        commandPC += " ";
                }
            } while (!computeCommand(s, commandPC, false));
            cout << s;
            outputFile << commandPC << "\n";
        }
        outputFile.close();
        return 0;
    }
    else
    {
        cout << "Partita computer vs computer\n";
        Scacchiera s = Scacchiera();
        cout << "Scacchiera iniziale: \n"
             << s << "\n";
        int mosseMax = 30;
        ofstream outputFile("output.txt");
        outputFile.clear();
        while (!s.isScacco() && !s.isPatta() && !s.isScaccoMatto() && mosseMax > 0)
        {
            cout << "computer 1: ";
            string commandPC1 = "";
            do
            {
                int c1[5];
                commandPC1 = "";
                for (int i = 0; i < 5; i++)
                {
                    c1[i] = rand() % 8;
                    if (i != 2)
                        commandPC1 += to_string(c1[i]);
                    else
                        commandPC1 += " ";
                }
            } while (!computeCommand(s, commandPC1, false));
            cout << s;
            outputFile << commandPC1 << "\n";

            sleep_for(seconds(1)); // 1 secondo da una giocata all'altra

            cout << "computer 2: ";
            string commandPC2 = "";
            do
            {
                int c1[5];
                commandPC2 = "";
                for (int i = 0; i < 5; i++)
                {
                    c1[i] = rand() % 8;
                    if (i != 2)
                        commandPC2 += to_string(c1[i]);
                    else
                        commandPC2 += " ";
                }
            } while (!computeCommand(s, commandPC2, false));
            cout << s;
            outputFile << commandPC2 << "\n";
        }
        return 0;
    }
}