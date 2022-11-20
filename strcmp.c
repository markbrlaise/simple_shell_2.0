#include "main.h"

int _strcmp(const char *s1, const char *s2)
{
	int i = 0;
	int diff;

	while (s1[i])
	{
		diff =+ (s1[i] - s2[i]);
		++i;
	}

	return (diff);
}
