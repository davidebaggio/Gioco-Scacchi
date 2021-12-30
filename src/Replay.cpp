// Baggio Davide
#include <iostream>
#include <fstream>
#include <string.h>
#include <chrono>
#include <thread>
#include "../include/Scacchiera.h"

using namespace std;

void computeCommand(Scacchiera &sca, const string &cmd)
{
	int xi = ((int)cmd[0]) - 65; //-65 per ascii table A
	int yi = ((int)cmd[1]) - 49; //-49 per ascii table 1
	int xf = ((int)cmd[3]) - 65; //-65 per ascii table B
	int yf = ((int)cmd[4]) - 49; //-49 per ascii table 3
	Pedina &temp = *sca.getPedina(xi, yi);				//<----------------------------------------------------
	temp.move(xf, yf, sca);
}

int main(int argc, char *argv[])
{
	using namespace std::this_thread; // sleep_for
	using namespace std::chrono;	  // seconds

	if (argc <= 1 || argc > 3)
	{
		cout << "[Error] Incorrect arguments. Type: " << endl
			 << "\t [input_file_name]: to watch the replay of the match." << endl
			 << "\t [input_file_name] [output_file_name]: to watch the replay on the output file." << endl;
		return 0;
	}
	else if (argc == 2)
	{
		ifstream inputFile(argv[1]);
		if (!inputFile.is_open())
		{
			cout << "[Error] File = " << argv[1] << " not found\n";
			return 0;
		}
		else
		{
			cout << "Replay on command prompt\n";
			Scacchiera s = Scacchiera();
			cout << "Scacchiera iniziale: \n"
				 << s << "\n";
			string command;
			int g = 1;
			while (getline(inputFile, command))
			{
				if (g > 0)
				{
					cout << "Player 1: \n";
					computeCommand(s, command);
					cout << s;
				}
				else
				{
					cout << "Player 2: \n";
					computeCommand(s, command);
					cout << s;
				}
				g *= -1;
				sleep_for(seconds(1)); // 1 secondo da una giocata all'altra
			}
		}
		inputFile.close();
	}
	else
	{
		ifstream inputFile(argv[1]);
		ofstream outputFile(argv[2]);
		if (!inputFile.is_open() || !outputFile.is_open())
		{
			cout << "[Error] Cannot open argument files. Check file names again.\n";
			return 0;
		}
		else
		{
			outputFile.clear();
			cout << "Replay on [file] = " << argv[2];
			Scacchiera s = Scacchiera();
			outputFile << "Scacchiera iniziale: \n"
					   << s << "\n";
			string command;
			int g = 1;
			while (getline(inputFile, command))
			{
				if (g > 0)
				{
					outputFile << "Player 1: \n";
					computeCommand(s, command);
					outputFile << s;
				}
				else
				{
					outputFile << "Player 2: \n";
					computeCommand(s, command);
					outputFile << s;
				}
				g *= -1;
				sleep_for(seconds(1)); // 1 secondo da una giocata all'altra
			}
			inputFile.close();
			outputFile.close();
			return 0;
		}

		return 0;
	}
}