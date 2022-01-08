// Baggio Davide
#include <iostream>
#include <fstream>
#include <string.h>
#include <chrono>
#include <thread>
#include "../include/Scacchiera.h"

using namespace std;

/**
 * @brief Funzione che trasforma un opportuno comando in coordinate della scacchiera (da char a int)
 * e muove la pedina nella scacchiera di conseguenza. Non vengono fatti controlli perchè il programma
 * svolge replay di partite con mosse già validate.
 *
 * @param sca Riferimento alla Scacchiera
 * @param cmd Stringa del comando
 */
void computeCommand(Scacchiera &sca, const string &cmd, const string &special)
{
	int xi = ((int)cmd[0]) - 65; //-65 per ascii table A
	int yi = ((int)cmd[1]) - 49; //-49 per ascii table 1
	int xf = ((int)cmd[3]) - 65; //-65 per ascii table B
	int yf = ((int)cmd[4]) - 49; //-49 per ascii table 3
	Pedina *temp = sca.getPedina(xi, yi);
	if (special == "")
		sca.move(temp, xf, yf);
	else if (special == "ArroccoN" || special == "ArroccoB")
		sca.arrocco(xi, yi, xf, yf);
	else if ((int)special[0] < 64)
		sca.replayPromo(temp, special, false);
	else if ((int)special[0] > 64)
		sca.replayPromo(temp, special, true);
}

/**
 * @brief Entry point dell'eseguibile Replay.exe. Gestisce il replay di una partita
 *
 * @param argc Accetta al massimo 3 argomenti: l'eseguibile, il file di lettura del replay e il
 * file di scrittura del replay.
 * @param argv
 * @return int 0.
 */
int main(int argc, char *argv[])
{
	/**
	 * @brief std::this_thread e std::chrono verranno usati
	 * per far passare il tempo di 1 secondo da ogni giocata stampata su Prompt dei comandi.
	 */
	using namespace std::this_thread; // sleep_for
	using namespace std::chrono;	  // seconds

	// Se si avvia Replay.exe con argomenti non corretti.
	if (argc <= 1 || argc > 3)
	{
		cout << "[Error] Incorrect arguments. Type: " << endl
			 << "\t [input_file_name]: to watch the replay of the match." << endl
			 << "\t [input_file_name] [output_file_name]: to watch the replay on the output file." << endl;
		return 0;
	}

	// Se si avvia Replay.exe [input_file_name]
	else if (argc == 2)
	{
		// Apertura di file di log dove verranno lette tutte le mosse.
		ifstream inputFile(argv[1]);
		ifstream spec("spec.txt");
		if (!inputFile.is_open())
		{
			cout << "[Error] File = " << argv[1] << " not found\n";
			return 0;
		}
		else
		{
			cout << "Replay on command prompt\n";

			// Inizializzazione Scacchiera
			Scacchiera s{};
			cout << "Scacchiera iniziale: \n"
				 << s << "\n";

			string command;
			int g = 1;

			// Lettura dei comandi da inputFile affinchè non sono terminati.
			while (getline(inputFile, command))
			{
				string special;
				// Giocatore 1
				if (g > 0)
				{
					getline(spec, special);
					cout << "Player 1: \n";
					computeCommand(s, command, special);
					cout << command << "\n";
					cout << s << "\n\n";
				}

				// Giocatore 2
				else
				{
					getline(spec, special);
					cout << "Player 2: \n";
					computeCommand(s, command, special);
					cout << command << "\n";
					cout << s << "\n\n";
				}

				// Cambio giocatore ogni turno
				g *= -1;

				sleep_for(seconds(1)); // 1 secondo da una giocata all'altra
			}
		}
		spec.close();
		inputFile.close();
	}

	// Se si avvia Replay.exe [input_file_name] [output_file_name]
	else
	{
		// Apertura dei file di log dove verranno lette tutte le mosse e stampato il replay della partita.
		ifstream inputFile(argv[1]);
		ofstream outputFile(argv[2]);
		ifstream spec("spec.txt");
		if (!inputFile.is_open() || !outputFile.is_open())
		{
			cout << "[Error] Cannot open argument files. Check file names again.\n";
			return 0;
		}
		else
		{
			outputFile.clear();
			cout << "Replay on [file] = " << argv[2];

			// Inizializzazione della Scacchiera
			Scacchiera s{};
			outputFile << "Scacchiera iniziale: \n"
					   << s << "\n";

			string command;
			int g = 1;

			// Lettura dei comandi da inputFile affinchè non sono terminati.
			while (getline(inputFile, command))
			{
				string special;
				if (g > 0)
				{
					getline(spec, special);
					outputFile << "Player 1: \n";
					computeCommand(s, command, special);
					outputFile << command << "\n";
					outputFile << s << "\n\n";
				}
				else
				{
					getline(spec, special);
					outputFile << "Player 2: \n";
					computeCommand(s, command, special);
					outputFile << command << "\n";
					outputFile << s << "\n\n";
				}

				// Cambio giocatore ogni turno.
				g *= -1;
			}
			inputFile.close();
			outputFile.close();
			spec.close();
			return 0;
		}
		return 0;
	}
}