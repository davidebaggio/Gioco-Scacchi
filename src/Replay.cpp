// Baggio Davide

#include <iostream>
#include <fstream>
#include <string.h>
#include "../include/Scacchiera.h"
#include "../include/RepGame.h"

using namespace std;

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

	RepGame repGame = RepGame();

	// Se si avvia Replay.exe con argomenti non corretti.
	if (argc <= 1 || argc > 3)
	{
		cout << "[Error] Incorrect arguments. Type: " << endl
			 << "\t [input_file_name]: to watch the replay of the match." << endl
			 << "\t [input_file_name] [output_file_name]: to watch the replay on the output file." << endl;
		return 0;
	}

	// Se si avvia Replay [input_file_name]
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
			repGame.ReplayLogToConsole(inputFile, spec);
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

			repGame.ReplayLogToLog(inputFile, outputFile, spec);

			inputFile.close();
			outputFile.close();
			spec.close();
		}
		return 0;
	}
}