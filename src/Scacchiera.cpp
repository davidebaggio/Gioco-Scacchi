//Luca Mainardi

#include "../include/Scacchiera.h"
#include "../include/Pezzi.h"

Scacchiera::Scacchiera()	//posiziona pedine nella posizione di partenza
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (i == 1)	//fila di pedoni bianchi
			{
				Pedone p = Pedone(j, i, true);
				matrice[i][j] = &p;
			}
			
			if(i == 0)	//fila con pedine bianche
			{
				if(j==0 || j ==7)
				{
					Torre t = Torre(j, i, true);
					matrice[i][j] = &t;
				}
				if(j==1 || j ==6)
				{
					Cavallo c = Cavallo(j, i, true);
					matrice[i][j] = &c;
				}
				if(j==2 || j ==5)
				{
					Alfiere a = Alfiere(j, i, true);
					matrice[i][j] = &a;
				}
				if(j==3)
				{
					Regina d = Regina(j, i, true);
					matrice[i][j] = &d;
				}
				if(j==4)
				{
					Re r = Re(j, i, true);
					matrice[i][j] = &r;
				}
				
			}

			if(i == 7)	//fila di pedoni neri
			{
				Pedone p = Pedone(j, i, false);
				matrice[i][j] = &p;
			}

			if(i == 7)	//fila con pedine nere
			{
				if(j==0 || j ==7)
				{
					Torre t = Torre(j, i, false);
					matrice[i][j] = &t;
				}
				if(j==1 || j ==6)
				{
					Cavallo c = Cavallo(j, i, false);
					matrice[i][j] = &c;
				}
				if(j==2 || j ==5)
				{
					Alfiere a = Alfiere(j, i, false);
					matrice[i][j] = &a;
				}
				if(j==3)
				{
					Regina d = Regina(j, i, false);
					matrice[i][j] = &d;
				}
				if(j==4)
				{
					Re r = Re(i, j, false);
					matrice[i][j] = &r;
				}
			}
			else matrice[i][j] = nullptr;
		}
	
	}
}