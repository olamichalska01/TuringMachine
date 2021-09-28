#include <stdio.h>
#include <stdlib.h>
#include "wynik.h"


int wynik(int m, int n) // obliczy wynik uzyskany przez maszyne
{
	int i = 0;
	int result = 0;


	if (m > n)
		result = m - n;
	else result = 0;


	return result;
}
