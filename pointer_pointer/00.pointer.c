#include <stdio.h>

/**
  * main - c pointer to another pointer
  * Return: Always 0
  */
int main()
{
	int var;
	int *ptr;
	int **pptr;

	var = 3000;
	ptr = &var;
	pptr = &ptr;

	printf("Value available at **pptr = %d\n", **pptr);

	return (0);
}
