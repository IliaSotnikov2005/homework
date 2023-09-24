#include <stdio.h>

int main()
{
	int numberOfAmounts[28] = { 0 };
	for (int number = 0; number < 1000; number++)
	{
		int sumOfDigits = number / 100 + number % 100 / 10 + number % 10;
		numberOfAmounts[sumOfDigits]++;
	}

	int numberOfHappyTickets = 0;
	for (int sumOfDigits = 0; sumOfDigits < 28; sumOfDigits++)
	{
		numberOfHappyTickets += numberOfAmounts[sumOfDigits] * numberOfAmounts[sumOfDigits];
	}

	printf("Number of lucky tickets = %d\n", numberOfHappyTickets);
}