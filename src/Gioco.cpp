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

/**
 * @brief Funzione di promozione per i pedoni
 *
 * @param sca Riferimento alla scacchiera in modo che possa cambiare il puntatore ad una nuova pedina
 * @param p La pedina da modificare (utile per le sue coordinate)
 * @param player Parametro aggiuntivo per la stampa dei messaggi allo std::ostream.
 */
void promozione(Scacchiera &sca, Pedina *p, bool player)
{
    if (p->getColor())
    {
        cout << "\nPromozione del Pedone Bianco\n";
        if (player)
        {
            cout << "Inserire la pedina con il quale vogliamo promuovere:\n";
            char name;
            do
            {
                cin >> name;
            } while (name != 't' && name != 'c' && name != 'a' && name != 'd' && name != 'r');
            int x = p->getX();
            int y = p->getY();
            Pedina *temp;
            if (name == 't')
                temp = new Torre(x, y, player, name);
            if (name == 'c')
                temp = new Cavallo(x, y, player, name);
            if (name == 'a')
                temp = new Alfiere(x, y, player, name);
            if (name == 'd')
                temp = new Regina(x, y, player, name);
            if (name == 'r')
                temp = new Re(x, y, player, name);
            sca.changePiece(x, y, temp);
        }
        else
        {
            int x = p->getX();
            int y = p->getY();
            Pedina *temp;
            if (y = 0)
                temp = new Regina(x, y, true, 'd');
            else
                temp = new Regina(x, y, false, 'd');
            sca.changePiece(x, y, temp);
        }
    }
    else
    {
        cout << "\nPromozione del pedone Nero\n";
        int x = p->getX();
        int y = p->getY();
        Pedina *temp = new Regina(x, y, false, 'd');
        sca.changePiece(x, y, temp);
    }
}

/**
 * @brief Funzione che controlla se il comando inserito da std::istream è di formato corretto
 * con caratteri da A a H e interi da 1 a 8.
 *
 * @param cmd La stringa del comando.
 * @return true Se il comando è di tipo prestabilito. Es: "A7 B3".
 * @return false Altrimenti
 */
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

/**
 * @brief Funzione che trasforma un opportuno comando in coordinate della scacchiera (da char a int)
 * e prova a muovere la pedina nella scacchiera di conseguenza.
 * In caso chiama la funzione promozione(Scacchiera&, Pedina*, bool) per controllare la promozione del pedone.
 * @param sca Riferimento alla scacchiera.
 * @param cmd La stringa del comando
 * @param col Colore del giocatore che deve essere uguale al colore della pedina da spostare.
 * @param err Parametro aggiuntivo per la stampa a std::ostream degli aventuali errori.
 * @return true Se la pedina viene mossa correttamente.
 * @return false Se la pedina non viene mossa. Vedi anche checkPos() delle pedine.
 */
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
        return false;
    }
    if (temp->getColor() != col)
    {
        if (err)
            cout << "Stai spostando la pedina dell'altro colore.\n";
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
        return false;
    }
    if ((temp->getName() == 'p' && temp->getY() == 0) || (temp->getName() == 'P' && temp->getY() == 7))
        promozione(sca, temp, err);
    return true;
}

/**
 * @brief Entry point dell'eseguibile Scacchiera.exe. Gestisce le partite
 *
 * @param argc Accetta al massimo 2 argomenti: l'eseguibile e gli argomenti da riga di comando
 *             -pc: per le partite giocatore vs PC
 *             -cc: per le partite PC vs PC
 * @param argv
 * @return int 0.
 */
int main(int argc, char *argv[])
{
    srand(time(NULL));

    /**
     * @brief std::this_thread e std::chrono verranno usati
     * per far passare il tempo di 1 secondo da ogni giocata PC vs PC.
     */
    using namespace std::this_thread;
    using namespace std::chrono;

    // Se si avvia Scacchiera.exe senza argomenti
    if (argc <= 1)
    {
        cout << "[Error] Not enough arguments. Type: " << endl
             << "\t -pc: to play vs computer." << endl
             << "\t -cc: to watch a match computer vs computer." << endl;
        return 0;
    }

    // Se si avvia Scacchiera.exe con argomenti errati
    else if (strcmp(argv[1], "-pc") != 0 && strcmp(argv[1], "-cc") != 0)
    {
        cout << "[Error] Incorrect arguments. Type: " << endl
             << "\t -pc: to play vs computer." << endl
             << "\t -cc: to watch a match computer vs computer." << endl;
        return 0;
    }

    // Se si avvia Scacchiera.exe -pc (Partita Giocatore vs PC)
    else if (strcmp(argv[1], "-pc") == 0)
    {
        cout << "Partita giocatore (Bianco) vs computer (Nero)\n";
        cout << "Per giocare inserire la posizione di cella iniziale e finale separati da uno spazio. Es: A2 C3\n";

        // Inizializzazione scacchiera.
        Scacchiera s{};
        cout << "Scacchiera iniziale: \n"
             << "\n"
             << s << "\n";

        // Apertura di file di log dove verranno salvate tutte le mosse.
        ofstream outputFile("logPC.txt");
        outputFile.clear();

        // Ciclo per la partita, continua finchè una delle condizioni non sia verificata
        while (s.isScacco() == 0 && !s.isPatta() && s.isScaccoMatto() == 0)
        {

            cout << "Player: \n";
            string commandPL;

            // Inserimento del comando attraverso std::istream affinchè non sia valido.
            do
            {
                getline(cin, commandPL);
            } while (!computeCommand(s, commandPL, true, true));

            cout << "\n"
                 << s << "\n";

            outputFile << commandPL << "\n";

            cout << "Computer: \n";
            string commandPC = "";

            // Estrazione casuale del comando da parte del PC affinchè non sia valido.
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
            } while (!computeCommand(s, commandPC, false, false));

            cout << commandPC << "\n"
                 << s << "\n";

            outputFile << commandPC << "\n";
        }

        /**
         * @brief Stampa delle condizioni per il quale la partita si è interrotta.
         *
         */
        if (s.isScaccoMatto() == 1 || s.isScacco() == 1)
        {
            cout << "Giocatore sotto scacco\n";
        }
        else if (s.isScaccoMatto() == 2 || s.isScacco() == 2)
        {
            cout << "Computer sotto scacco\n";
        }
        else if (s.isPatta())
        {
            cout << "E' patta\n";
        }
        outputFile.close();
        return 0;
    }

    // Se si avvia Scacchiera.exe -cc (Partita PC vs PC)
    else
    {
        cout << "Partita computer vs computer\n";

        // Inizializzazione scacchiera.
        Scacchiera s{};
        cout << "Scacchiera iniziale: \n"
             << "\n"
             << s << "\n";

        // PC vs PC ha un massimo di mosse
        int mosseMax = 30;

        // Apertura di file di log dove verranno salvate tutte le mosse.
        ofstream outputFile("logCC.txt");
        outputFile.clear();

        // Ciclo per la partita, continua finchè una delle condizioni non sia verificata
        while (!s.isScacco() && !s.isPatta() && !s.isScaccoMatto() && mosseMax > 0)
        {
            cout << "computer 1: \n";
            string commandPC1 = "";

            // Estrazione casuale del comando da parte del PC affinchè non sia valido.
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
            } while (!computeCommand(s, commandPC1, true, false));

            cout << commandPC1 << "\n"
                 << s << "\n";
            outputFile << commandPC1 << "\n";

            sleep_for(seconds(1)); // 1 secondo da una giocata all'altra

            cout << "computer 2: \n";
            string commandPC2 = "";

            // Estrazione casuale del comando da parte del PC affinchè non sia valido.
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
                        commandPC2 += c1;
                    else
                        commandPC2 += " ";
                }
            } while (!computeCommand(s, commandPC2, false, false));

            cout << commandPC2 << "\n"
                 << s << "\n";

            outputFile << commandPC2 << "\n";

            mosseMax--;

            sleep_for(seconds(1)); // 1 secondo da una giocata all'altra
        }

        /**
         * @brief Stampa delle condizioni per il quale la partita si è interrotta.
         *
         */
        if (s.isScacco() == 1 || s.isScaccoMatto() == 1)
        {
            cout << "PC1 sotto scacco\n";
        }
        else if (s.isScacco() == 2 || s.isScaccoMatto() == 2)
        {
            cout << "PC2 sotto scacco\n";
        }
        else if (s.isPatta())
        {
            cout << "E' patta\n";
        }
        outputFile.close();
        return 0;
    }
}

/**
 * @brief Secondo Entry point per debug.
 *
 * @return int 0.
 */
int main2()
{
    Scacchiera s{};
    cout << "Scacchiera iniziale: \n";
    cout << s << "\n";

    Pedina *temp = s.getPedina(1, 6);
    promozione(s, temp, true);

    cout << s;
    return 0;
}