#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ciag_wejsciowy.h"


char* generate_sequence(int m, int n) // generuje ciag wejsciowy do maszyny
{
	char* start_sequence;
	int i;

	start_sequence = (char*)calloc(m + n + 1, (m + n + 1) * sizeof(char));

	for (i = 0; i < m + n + 1; i++)
	{
		if (i < m)
		{
			start_sequence[i] = '0';
		}
		else if (i == m)
		{
			start_sequence[i] = '1';
		}
		else if (i > m && i < n + m + 1)
		{
			start_sequence[i] = '0';
		}
	}

	return start_sequence;
}