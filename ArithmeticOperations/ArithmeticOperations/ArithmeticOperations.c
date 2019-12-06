//-----------------------------------------------------------------------------
// ArithmeticOperations.c
// Stubs for required functions.
//-----------------------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

// Define fptr_t type using typedef statement
typedef int (*fptr_t)(int, int);

// Define functions
int sum(int x, int y) {
	return x + y;
}

int diff(int x, int y) {
	return x - y;
}

int prod(int x, int y) {
	return x * y;
}

int quot(int x, int y) {
	return x / y;
}

int rem(int x, int y) {
	return x % y;

}

int apply(fptr_t fp, int x, int y) {
	return fp(x, y);

}

int compute(fptr_t fcn[5], int* A, int* idx, int n) {
	//loop through the array n times, and perform the correspobding operations
	int result = A[0];

	for (int i = 0; i < n; i++)
	{
		if (idx[i] == 0)
		{
			result = sum(result, A[i + 1]);
		}
		else if (idx[i] == 1)
		{
			result = diff(result, A[i + 1]);
		}
		else if (idx[i] == 2)
		{
			result = prod(result, A[i + 1]);
		}
		else if (idx[i] == 3)
		{
			result = quot(result, A[i + 1]);
		}
		else if (idx[i] == 4)
		{
			result = rem(result, A[i + 1]);
		}
	}

	return result;

}

void testCompute() {

	fptr_t op[] = { sum, diff, prod, quot, rem };
	int A[] = { 3, 2, 5, 4, 6, 7, 9, 2, 8 };
	int opCode[] = { 0, 2, 1, 4, 2, 2, 3, 1 };
	int n = 8;

	//--------------------------------------------------------------------------
	// prints 86, which is the value of the value of the expression:
	//
	//               (((((((3+2)*5)-4)%6)*7)*9)/2)-8
	//
	//--------------------------------------------------------------------------
	printf("%d\n", compute(op, A, opCode, n));
}

int main(int argc, char* argv[]) {
	FILE* in;
	FILE* out;
	char* line;
	int str[100];
	
	

	if ((in = fopen(argv[1], "r")) == NULL) {
		printf("Unable to read from file %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}
	if ((in = fopen(argv[1], "w")) == NULL) {
		printf("Unable to write to file %s\n", argv[2]);
		exit(EXIT_FAILURE);
	}
	line = calloc(100, sizeof(int));
	assert(line != NULL);

	//line 1 is n
	//line 2 is operations
	//line 3 is operands

	//put all the numbers in one string
	while (fgets(line, 100, in) != NULL) {
		fscanf
		
	}

	testCompute();  // output should be 86

	return EXIT_SUCCESS;
}
