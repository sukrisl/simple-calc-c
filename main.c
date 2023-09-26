#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_INPUT_STR			100

#define INVALID_SIGN			0
#define PLUS_SIGN				1
#define MINUS_SIGN				2
#define MULTIPLICATION_SIGN		3
#define DIVISION_SIGN			4

int isOperator(char input) {
	int op = INVALID_SIGN;
	
	if (input == '+') {
		op = PLUS_SIGN;
	} else if (input == '-') {
		op = MINUS_SIGN;
	} else if (input == '*') {
		op = MULTIPLICATION_SIGN;
	} else if (input == '/') {
		op = DIVISION_SIGN;
	}
	
	return op;
}

int parseString(char* str, double* result) {
	int digit;
	int op = INVALID_SIGN;
	double out = 0;
	char digitStr[MAX_INPUT_STR] = {'\0'}; // Initialized buffer with null character to make sure digit string buffer is empty

	int i = 0;
	char token = str[0];
	
	while (token != '\0') {
		token = str[i];
		i++;
		
		// Check if token is digit, then append token to digit buffer
		if (isdigit(token)) { 
			int j = 0;
			while (digitStr[j] != '\0') j++;
			digitStr[j] = token;
			continue; // Skip iteration if token is a number
		}
		
		if (token == ' ') continue; // Ignore space token, skip current iteration
		digit = atoi(digitStr);	// Convert digit string to integer number to perform calculation
		
		// Calculate result according to last operator received
		if (op == PLUS_SIGN) {
			*result += digit;
		} else if (op == MINUS_SIGN) {
			*result -= digit;
		} else if (op == MULTIPLICATION_SIGN) {
			*result *= digit;
		} else if (op == DIVISION_SIGN) {
			*result /= digit;
		} else {
			*result = digit;
		}
		
		// Update operator
		op = isOperator(token);

		// Check if operator is valid
		if (!op && token != '\0') return 0;
		
		// Reset data buffer
		int j = 0;
		while (digitStr[j] != '\0') {
			digitStr[j] = '\0';
			j++;
		}
	}
	
	return 1;
}

int main(int argc, char *argv[]) {
	printf("===============================================================================\n");
	printf("                                Calculator App\n");
	printf("===============================================================================\n");
	printf("Valid operator:\n");
	printf("(+) Addition\n");
	printf("(-) Substraction\n");
	printf("(*) Multiplication\n");
	printf("(/) Division\n");
	printf("! The app calculate the input sequentially and do not accept brackets !\n");
	printf("! The app cannot compute fraction numbers, division operation will be rounded !\n");
	printf("===============================================================================\n");
	
	printf("Input arithmetic equation: ");
	
	// String buffer to hold user input
	char formulaStr[MAX_INPUT_STR];
	
	// Get user input
	scanf("%[^\n]s", formulaStr);
	
	// Parse input string and perform calculation
	double result = 0;
	if (!parseString(formulaStr, &result)) {
		printf("Cannot compute! Input invalid.\n");
		return 1;
	}
	
	// Print out the calculation result
	printf("The result is %s = %.0f\n", formulaStr, result);
	
	return 0;
}
