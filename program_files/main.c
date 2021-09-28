#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ciag_wejsciowy.h"
#include "wynik.h"
#include "opisy_chwilowe.h"


void description() // opis maszyny
{
	printf("                               _______________________________________________________\n");
	printf("                              |                                                       |");
	printf("\n                              | Emulator maszyny Turinga obliczajacy roznice wlasciwa |\n");
	printf("                              |_______________________________________________________|");

	printf("\n\n Postac maszyny Turinga:\n\n");
	printf(" M = ({ q0, q1, q2, q3, q4, q5, q6 }, { 0, 1 }, { 0, 1, B }, delta, q0, B, 0)\n\n");
}

int main()
{
	int m;
	int n;
	int result = 0;
	char* ciag;
	char* stan = "(q0)";
	
	description();

	printf(" Wprowadz m >> ");
	scanf("%d", &m);
	printf(" Wprowadz n >> ");
	scanf("%d", &n);
	printf("\n");

	if ((m < 0 || n < 0) || (m == 0 && n == 0))
	{
		printf("\n Obie liczby powinny byc nieujemne i conajmniej jedna powinna byc wieksza od zera!\n Przykladowe poprawne dane: m = 2, n = 0 lub m = 1, n = 8 \n");
		return 1;
	}
	printf(" Ciag startowy: %s", generate_sequence(m, n));
	printf("\n\n");

	ciag = (char*)calloc(m+n+5, (m+n+5) * sizeof(char));
	strcpy(ciag, stan);
	strcat(ciag, generate_sequence(m, n));

	printf(" %s  ", ciag);
	
	while(strstr(ciag, "6") == NULL && strstr(ciag, "(q0)B") == NULL && strstr(ciag, "(q1)B") == NULL)
		podziel_slowo(ciag, m, n);


	
	result = wynik(m, n);
	printf("\n\n Wynik: %d\n", result);

	return 0;
}