// Davide Baggio

#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>
#include <cstdlib>
#include <time.h>
#include <vector>

#include "Scacchiera.h"
#include "Pezzi.h"

using namespace std;

class Game
{
public:
	string randomCommand();
	bool isValid(const string &);
	bool computeCommand(ofstream &, Scacchiera &, const string &, bool, bool);

	bool canEnPassant(Scacchiera &, Pedina *, int, int);

	void startPC();
	void startCC();
};

#endif // GAME_H