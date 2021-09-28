#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ciag_wejsciowy.h"
#include "wynik.h"

char q0[][6] = { "B(q1)", "B(q5)" };
char q1[][6] = { "0(q1)", "1(q2)" };
char q2[][6] = { "(q3)1", "1(q2)", "(q4)B" };
char q3[][6] = { "(q3)0", "(q3)1", "B(q0)" };
char q4[][6] = { "(q4)0", "(q4)B", "0(q6)" };
char q5[][6] = { "B(q5)", "B(q5)", "B(q6)" };

char* zmiana(char stan, char znak) // funkcja sprawdzająca na co zamieniamy 
{
	switch (stan)
	{
		case '0':
		{
			switch (znak)
			{
			case '0':
				return q0[0];
				break;
			case '1':
				return q0[1];
				break;
			}
	
			break;
		}	

		case '1':
		{
			switch (znak)
			{
			case '0':
				return q1[0];
				break;
			case '1':
				return q1[1];
				break;
			}
			break;

			break;
		}

		case '2':
		{
			switch (znak)
			{
			case '0':
				return q2[0];
				break;
			case '1':
				return q2[1];
				break;
			case 'B':
				return q2[2];
				break;
			}
			break;

			break;
		}

		case '3':
		{
			switch (znak)
			{
			case '0':
				return q3[0];
				break;
			case '1':
				return q3[1];
				break;
			case 'B':
				return q3[2];
				break;
			}
			break;

			break;
		}

		case '4':
		{
			switch (znak)
			{
			case '0':
				return q4[0];
				break;
			case '1':
				return q4[1];
				break;
			case 'B':
				return q4[2];
				break;
			}
			break;

			break;
		}

		case '5':
		{
			switch (znak)
			{
			case '0':
				return q5[0];
				break;
			case '1':
				return q5[1];
				break;
			case 'B':
				return q5[2];
				break;
			}
			break;

			break;
		}
	}

}

void podziel_slowo(char* ciag, int m, int n)
{
	int j = 0, i = 0;
	int koniec_przed = 0; // numer pola ostatniego znaku przed znakiem przed numerem stanu tzn w takim ciagu: 00(q1)010   koniec_przed = 0; 
	char* przed;
	char* znak_przed;
	char* stan;
	char* znak_po;
	char* po;

	przed = (char*)calloc(strlen(ciag), sizeof(char)); // jesli ciag wyglada tak: 000(q1)0010 to to jest miejsce na 00
	znak_przed = (char*)calloc(strlen(ciag), sizeof(char)); // miejsce na znak przed stanem 
	stan = (char*)calloc(strlen(ciag), sizeof(char)); // miejsce na (q*)
	znak_po = (char*)calloc(strlen(ciag), sizeof(char)); // miejsce na znak po stanie
	po = (char*)calloc(strlen(ciag), sizeof(char));  // jesli ciag wyglada tak: 000(q1)0010 to to jest miejsce na 010

	// podzial slowa na 5 czesci:
	for (; i < strlen(ciag); i++) // petla wykrywajaca miejsce w ktorym jest ostatni znak z czesci o nazwie przed
	{
		if (ciag[i] == '(')
		{
			koniec_przed = i - 2;
		}
	}
		
	stan[0] = ciag[koniec_przed + 2];
	stan[1] = ciag[koniec_przed + 3];
	stan[2] = ciag[koniec_przed + 4];
	stan[3] = ciag[koniec_przed + 5];
	
	if (koniec_przed + 6 != strlen(ciag)) // wykrywa czy jest jakis znak po stanie, jesli tak to zapisuje go
	{
		znak_po[0] = ciag[koniec_przed + 6];
	}

	if (koniec_przed >= -1) // wykrywa czy jest jakis znak przed stanem, jesli tak to zapisuje go
	{
		znak_przed[0] = ciag[koniec_przed + 1];
	}

	for (i = koniec_przed + 7; i < strlen(ciag); i++) // wykrywa czesc po znak_po
	{
		po[j] = ciag[i];
		j++;
	}
	
	j = 0;
	
	for (i = 0; i < koniec_przed + 1; i++)
	{
		przed[j] = ciag[i];
		j++;
	}


	char znak = znak_po[0];
	char st = stan[2];
	
	zmiana(st, znak);


	// normalne przejscie w prawo
	if ((zmiana(st, znak) == q0[0] || zmiana(st, znak) == q0[1] || zmiana(st, znak) == q1[0] || zmiana(st, znak) == q1[1] || zmiana(st, znak) == q2[1] || zmiana(st, znak) == q3[2] || zmiana(st, znak) == q4[2] || zmiana(st, znak) == q5[0] || zmiana(st, znak) == q5[1] || zmiana(st, znak) == q5[2]) && strlen(po) >= 1)
	{
		strcat(stan, po);
		strcpy(stan, zmiana(st, znak));
		strcat(przed, znak_przed);
		strcat(przed, stan);
		strcat(przed, po);
		strcpy(ciag, przed);
	}

	// przejscie w prawo gdy trzeba dopisac B
	if ((zmiana(st, znak) == q0[0] || zmiana(st, znak) == q0[1] || zmiana(st, znak) == q1[0] || zmiana(st, znak) == q1[1] || zmiana(st, znak) == q2[1] || zmiana(st, znak) == q3[2] || zmiana(st, znak) == q4[2] || zmiana(st, znak) == q5[0] || zmiana(st, znak) == q5[1] || zmiana(st, znak) == q5[2]) && strlen(po) < 1)
	{
		strcat(stan, po);
		strcpy(stan, zmiana(st, znak));
		strcat(przed, znak_przed);
		strcat(przed, stan);
		po = (char*)realloc(po, (strlen(ciag) + 1) * sizeof(char));
		strcat(po, "B");
		strcat(przed, po);
		strcpy(ciag, przed);
	}

	// normalne przejscie w lewo
	if ((zmiana(st, znak) == q2[0] || zmiana(st, znak) == q2[2] || zmiana(st, znak) == q3[0] || zmiana(st, znak) == q3[1] || zmiana(st, znak) == q4[0] || zmiana(st, znak) == q4[1]) && strlen(przed) >= 1)
	{
		strncpy(stan, zmiana(st, znak), 4);
		strcat(stan, znak_przed);
		strncat(stan, &zmiana(st, znak)[4], 1);
		strcat(przed, stan);
		strcat(przed, po);
		strcpy(ciag, przed);
	}

	// przejscie w lewo gdy trzeba dopisac B
	if ((zmiana(st, znak) == q2[0] || zmiana(st, znak) == q2[2] || zmiana(st, znak) == q3[0] || zmiana(st, znak) == q3[1] || zmiana(st, znak) == q4[0] || zmiana(st, znak) == q4[1]) && strlen(przed) < 1)
	{
		stan = (char*)realloc(stan, (strlen(stan) + 1) * sizeof(char));
		strcpy(stan, "B");
		strncpy(stan, zmiana(st, znak), 4);
		strcat(stan, znak_przed);
		strncat(stan, &zmiana(st, znak)[4], 1);
		strcat(przed, stan);
		strcat(przed, po);
		strcpy(ciag, przed);
	}


	printf("|-  %s  ", ciag);
}