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

bool canEnPassant(Scacchiera &sca, Pedina *p, int xf, int yf)
{
    // controllo se destinazione e' occupata da un pedone
    Pedina *target;
    if (!sca.isEmpty(xf, yf))
    {
        target = sca.getPedina(xf, yf);
        // controlla che target sia un pedone
        if (target->getName() != 'p' || target->getName() != 'P')
            return false;
    }
    else
    {
        return false;
    }
    // controlla se destinazione  e' occupata da un pedone
    if (p->getName() != 'p' || p->getName() != 'P')
        return false;

    if (p->getName() == 'p') // pedone bianco
    {
        if (p->getY() != 3)
            return false;
    }
    else // pedone nero
    {
        if (p->getY() != 4)
            return false;
    }

    // controlla se target ha eseguito solo un movimento (che e' di due caselle)
    if (target->getMoveCount() != 1)
        return false;

    // controlla se destinazione e' di fianco al pedone (unica da verificare)
    if (yf == p->getY() && (xf == p->getX() - 1 || xf == p->getX() + 1))
        return true;

    return false;
}
/**
 * @brief Funzione di promozione per i pedoni
 *
 * @param sca Riferimento alla scacchiera in modo che possa cambiare il puntatore ad una nuova pedina
 * @param p La pedina da modificare (utile per le sue coordinate)
 * @param player Parametro aggiuntivo per la stampa dei messaggi allo std::ostream.
 */
/* void promozione(Scacchiera &sca, Pedina *p, bool player)
{
} */

string randomCommand()
{
    char c1;
    string commandPC = "";
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
    return commandPC;
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
bool computeCommand(ofstream &spec, Scacchiera &sca, const string &cmd, bool col, bool err) // funzione che trasforma il comado 'stringa' in coordinate di partenza e arrivo della pedina
{
    if (!isValid(cmd))
        return false;
    int xi = ((int)cmd[0]) - 65;       //-65 per ascii table A
    int yi = 7 - (((int)cmd[1]) - 49); //-49 per ascii table 0
    int xf = ((int)cmd[3]) - 65;       //-65 per ascii table A
    int yf = 7 - (((int)cmd[4]) - 49); //-49 per ascii table 0

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
        // cattura en passant
        if (canEnPassant(sca, temp, xf, yf))
        {
            sca.enPassant(temp, xf, yf);
        }
        // comando per arrocco   (si indicano la posizione del re e della torre che si vogliono spostare con l'arrocco)
        //  le precondizioni vengono verificate anche nella funzione
        else if (xi == 4 && yi == 0 && yf == 0 && (xf == 0 || xf == 7)) // arrocco nero
        {
            sca.arrocco(xi, yi, xf, yf);
            cout << "Arrocco\n";
            spec << "ArroccoN\n";
        }
        else if (xi == 4 && yi == 7 && yf == 7 && (xf == 0 || xf == 7)) // arrocco bianco
        {
            sca.arrocco(xi, yi, xf, yf);
            cout << "Arrocco\n";
            spec << "ArroccoB\n";
        }
        else
        {
            sca.move(temp, xf, yf);
            // promozione
            if ((temp->getName() == 'p' && temp->getY() == 0) || (temp->getName() == 'P' && temp->getY() == 7))
            {
                sca.promozione(spec, temp, err);
            }
            else
            {
                spec << "\n";
            }
        }
    }
    catch (const InvalidPosition &e)
    {
        if (err)
            cout << "Mossa non consentita.\n";
        return false;
    }
    catch (const InvalidIndex &e)
    {
        if (err)
            cout << "Mossa non consentita: giocatore sotto scacco.\n";
        return false;
    }

    return true;
}

/**
 * @brief Entry point dell'eseguibile Scacchiera. Gestisce le partite
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

    // Se si avvia Scacchiera senza argomenti
    if (argc <= 1)
    {
        cout << "[Error] Not enough arguments. Type: " << endl
             << "\t -pc: to play vs computer." << endl
             << "\t -cc: to watch a match computer vs computer." << endl;
        return 0;
    }

    // Se si avvia Scacchiera con argomenti errati
    else if (strcmp(argv[1], "-pc") != 0 && strcmp(argv[1], "-cc") != 0)
    {
        cout << "[Error] Incorrect arguments. Type: " << endl
             << "\t -pc: to play vs computer." << endl
             << "\t -cc: to watch a match computer vs computer." << endl;
        return 0;
    }

    // Se si avvia Scacchiera -pc (Partita Giocatore vs PC)
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
        ofstream spec("spec.txt");
        outputFile.clear();
        spec.clear();

        vector<string> cmd{};

        // Ciclo per la partita, continua finchè una delle condizioni non sia verificata
        while (!s.isPatta(cmd) && s.isScaccoMatto() == 0)
        {

            cout << "Player: \n";
            string commandPL;

            // Inserimento del comando attraverso std::istream affinchè non sia valido.
            do
            {
                getline(cin, commandPL);
            } while (!computeCommand(spec, s, commandPL, true, true));

            cmd.push_back(commandPL);
            outputFile << commandPL << "\n";

            // controlla se computer e' sotto scacco
            if (s.isScacco() == 2)
            {
                cout << "Computer sotto scacco\n";
                outputFile << "Computer sotto scacco\n";
            }

            cout << "\n"
                 << s << "\n";

            cout << "Computer: \n";
            string commandPC = "";

            // Estrazione casuale del comando da parte del PC affinchè non sia valido.
            do
            {
                commandPC = randomCommand();
            } while (!computeCommand(spec, s, commandPC, false, false));

            // stampa comando
            cmd.push_back(commandPC);
            cout << commandPC << "\n";
            outputFile << commandPC << "\n";

            // controlla se giocatore e' sotto scacco
            if (s.isScacco() == 1)
            {
                cout << "Giocatore sotto scacco\n";
            }
            // stampa scacchiera
            cout << s << "\n";
        }

        /**
         * @brief Stampa delle condizioni per il quale la partita si è interrotta.
         *
         */
        if (s.isScaccoMatto() == 1)
        {
            cout << "Giocatore sotto scacco matto\n";
        }
        else if (s.isScaccoMatto() == 2)
        {
            cout << "Computer sotto scacco matto\n";
        }
        else if (s.isPatta(cmd))
        {
            cout << "E' patta\n";
        }
        spec.close();
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
        ofstream spec("spec.txt");
        outputFile.clear();
        spec.clear();

        vector<string> cmd{};
        // Ciclo per la partita, continua finchè una delle condizioni non sia verificata
        while (!s.isPatta(cmd) && s.isScaccoMatto() == 0 && mosseMax > 0)
        {
            cout << "computer 1 (bianco): \n";
            string commandPC1 = "";

            // Estrazione casuale del comando da parte del PC affinchè non sia valido.
            do
            {
                commandPC1 = randomCommand();
            } while (!computeCommand(spec, s, commandPC1, true, false));

            // stampa il comando
            cmd.push_back(commandPC1);
            cout << commandPC1 << "\n";
            outputFile << commandPC1 << "\n";

            // stampa scacchiera
            cout << s << "\n";

            sleep_for(seconds(1)); // 1 secondo da una giocata all'altra

            cout << "computer 2 (nero): \n";
            string commandPC2 = "";

            // controlla se PC2 e' sotto scacco
            if (s.isScacco() == 2)
            {
                cout << "PC2 sotto scacco\n";
            }

            // Estrazione casuale del comando da parte del PC affinchè non sia valido.
            do
            {
                commandPC2 = randomCommand();
            } while (!computeCommand(spec, s, commandPC2, false, false));

            // stampa comando
            cmd.push_back(commandPC2);
            cout << commandPC2 << "\n";
            outputFile << commandPC2 << "\n";

            // stampa scacchiera
            cout << s << "\n";

            mosseMax--;

            sleep_for(seconds(1)); // 1 secondo da una giocata all'altra
        }

        /**
         * @brief Stampa delle condizioni per il quale la partita si è interrotta.
         *
         */
        if (s.isScaccoMatto() == 1)
        {
            cout << "PC1 sotto scacco matto\n";
        }
        else if (s.isScaccoMatto() == 2)
        {
            cout << "PC2 sotto scacco matto\n";
        }
        else if (s.isPatta(cmd))
        {
            cout << "E' patta\n";
        }
        else if (mosseMax == 0)
        {
            cout << "Raggiunto limite di mosse\n";
        }

        spec.close();
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

    Pedina *p1 = s.getPedina(5, 6);
    s.move(p1, 5, 4);
    s.move(p1, 5, 3);

    cout << s << "\n";

    Pedina *p2 = s.getPedina(4, 1);
    s.move(p2, 4, 3);

    cout << s << "\n";

    s.enPassant(p1, 4, 3);

    cout << s;
    return 0;
}