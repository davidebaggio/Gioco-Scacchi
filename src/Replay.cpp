#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

int main(int argc, char *argv[])
{
	if (argc <= 1)
	{
		cout << "[Error] Not enough arguments. Type: " << endl
			 << "\t [input_file_name]: to watch the replay of the match." << endl
			 << "\t [input_file_name] [output_file_name]: to watch the replay on the output file." << endl;
		return 0;
	}
	else if (argc == 2)
	{
		cout << "Replay on command prompt\n";
		return 0;
	}
	else if (argc == 3)
	{
		cout << "Replay on [file] = " << argv[2];
		return 0;
	}
	else
	{
		cout << "[Error] Too many arguments. Type: " << endl
			 << "\t [input_file_name]: to watch the replay of the match." << endl
			 << "\t [input_file_name] [output_file_name]: to watch the replay on the output file." << endl;
		return 0;
	}
}