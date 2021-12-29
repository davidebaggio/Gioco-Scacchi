#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

int main(int argc, char *argv[])
{
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
			inputFile.close();
			return 0;
		}
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
			cout << "Replay on [file] = " << argv[2];
			inputFile.close();
			return 0;
		}

		return 0;
	}
}