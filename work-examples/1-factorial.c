#include <stdio.h>
/**
  * factorial - factorial n using the recursion method
  * Return: 0
  */
int factorial(int n)
{
	if (n == 0)
	return (1);
	else
		return (n * factorial(n - 1));
}

int main(void)
{
	int f;
	f = factorial(20);
	printf("factorial (20) = %d\n", f);
	return (0);
}
