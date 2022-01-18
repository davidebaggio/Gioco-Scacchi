// Davide Baggio

#include "../include/Game.h"

string Game::randomCommand()
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

bool Game::isValid(const string &cmd) // funzione che controlla se il comando inserito è formattato in modo corretto
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

bool Game::canEnPassant(Scacchiera &sca, Pedina *p, int xf, int yf)
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

bool Game::computeCommand(ofstream &spec, Scacchiera &sca, const string &cmd, bool col, bool err) // funzione che trasforma il comado 'stringa' in coordinate di partenza e arrivo della pedina
{
	if (!isValid(cmd))
		return false;
	int xi = ((int)cmd[0]) - 65;	   //-65 per ascii table A
	int yi = 7 - (((int)cmd[1]) - 49); //-49 per ascii table 0
	int xf = ((int)cmd[3]) - 65;	   //-65 per ascii table A
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
	catch (const InvalidMove &e)
	{
		if (err)
			cout << "Mossa non consentita: giocatore sotto scacco.\n";
		return false;
	}

	return true;
}

void Game::startPC()
{
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
	// while (s.isPatta(cmd) != 3 && !s.isScaccoMattoBianco() && !s.isScaccoMattoNero())
	while (true)
	{
		//--------------------------- turno del bianco ---------------------------------
		if (s.isScaccoBianco())
		{
			cout << "Giocatore sotto scacco\n";
			outputFile << "Giocatore sotto scacco\n";
		}
		if (s.isPatta(cmd) == 1)
		{
			cout << "Patta: Bianco in stallo\n";
			break;
		}

		cout << "Player: \n";
		string commandPL;

		// Inserimento del comando attraverso std::istream affinchè non sia valido.
		do
		{
			getline(cin, commandPL);
			// cout<<commandPL<<endl;
		} while (!computeCommand(spec, s, commandPL, true, true));

		cmd.push_back(commandPL);
		outputFile << commandPL << "\n";

		// stampa scacchiera
		cout << "\n"
			 << s << "\n";

		// controlla se la partita e'finita
		if (s.isScaccoMattoNero())
		{
			cout << "Computer sotto scacco matto\n";
			break;
		}
		if (s.isPatta(cmd) == 3)
		{
			cout << "Patta: Mosse ripetute\n";
			break;
		}

		//--------------------------- turno del nero ---------------------------------
		// controlla se computer e' sotto scacco
		if (s.isScaccoNero())
		{
			cout << "Computer sotto scacco\n";
			outputFile << "Computer sotto scacco\n";
		}
		if (s.isPatta(cmd) == 2)
		{
			cout << "Patta: Nero in stallo\n";
			break;
		}

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

		// stampa scacchiera
		cout << s << "\n";

		// controlla se la partita e'finita
		if (s.isScaccoMattoBianco())
		{
			cout << "Giocatore sotto scacco matto\n";
			break;
		}
		if (s.isPatta(cmd) == 3)
		{
			cout << "Patta: Mosse ripetute\n";
			break;
		}
	}

	spec.close();
	outputFile.close();
}

void Game::startCC()
{
	Scacchiera s{};
	cout << "Scacchiera iniziale: \n"
		 << "\n"
		 << s << "\n";

	// PC vs PC ha un massimo di mosse
	int mosseMax = 50;

	// Apertura di file di log dove verranno salvate tutte le mosse.
	ofstream outputFile("logCC.txt");
	ofstream spec("spec.txt");
	outputFile.clear();
	spec.clear();

	vector<string> cmd{};
	// Ciclo per la partita, continua finchè una delle condizioni non sia verificata
	// while (s.isPatta(cmd) !=3 && !s.isScaccoMattoNero() && !s.isScaccoMattoBianco() && mosseMax > 0)
	while (mosseMax > 0)
	{
		cout << "Mossa " << 51 - mosseMax << endl;
		if (s.isScaccoBianco())
		{
			cout << "PC1 sotto scacco\n";
			outputFile << "PC1 sotto scacco\n";
		}
		if (s.isPatta(cmd) == 1)
		{
			cout << "Patta: PC1 in stallo\n";
			break;
		}

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

		// controlla se la partita e'finita
		if (s.isScaccoMattoNero())
		{
			cout << "Computer 2 sotto scacco matto\n";
			break;
		}
		if (s.isPatta(cmd) == 3)
		{
			cout << "Patta: Mosse ripetute\n";
			break;
		}

		//--------------------------- turno del nero ---------------------------------
		// sleep_for(seconds(1)); // 1 secondo da una giocata all'altra

		if (s.isScaccoNero())
		{
			cout << "PC2 sotto scacco\n";
			outputFile << "PC2 sotto scacco\n";
		}
		if (s.isPatta(cmd) == 2)
		{
			cout << "Patta: PC2 in stallo\n";
			break;
		}

		cout << "computer 2 (nero): \n";
		string commandPC2 = "";

		// controlla se PC2 e' sotto scacco

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

		// controlla se la partita e'finita
		if (s.isScaccoMattoBianco())
		{
			cout << "Computer 1 sotto scacco matto\n";
			break;
		}
		if (s.isPatta(cmd) == 3)
		{
			cout << "Patta: Mosse ripetute\n";
			break;
		}

		mosseMax--;

		// sleep_for(seconds(1)); // 1 secondo da una giocata all'altra
	}
	if (mosseMax == 0)
	{
		cout << "Raggiunto limite di mosse\n";
	}

	spec.close();
	outputFile.close();
}