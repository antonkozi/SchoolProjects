//-----------------------------------------------------------------------------
// Name: Anton Kozintsev
// Email: akozints@ucsc.edu
// ID: 1647521
// Dictionary.c
// Hash table implementation of the Dictionary ADT.
//-----------------------------------------------------------------------------
#include<stdlib.h>
#include<stdio.h>
#include<assert.h>
#include<string.h>
#include"Dictionary.h"

const int tableSize = 101;

// Private Types and Functions ------------------------------------------------

// NodeObj type
typedef struct NodeObj {
	char* key;
	char* val;
	struct NodeObj* next;
} NodeObj;

// Node type
typedef NodeObj* Node;

typedef struct DictionaryObj {
	Node* table;
	int numPairs;      // number of pairs in the dictionary
} DictionaryObj;

// newNode()
// constructor for the Node type
Node newNode(char* k, char* v) {
	Node N = malloc(sizeof(NodeObj));
	assert(N != NULL);
	N->key = k;
	N->val = v;
	N->next = NULL;
	return N;
}

// freeNode()
// destructor for the Node type
void freeNode(Node* pN) {
	if (pN != NULL && *pN != NULL) {
		free(*pN);
		*pN = NULL;
	}
}

// freeAllNodes()
// uses recursion to free all the Nodes in list headed by H
void freeAllNodes(Node H) {
	if (H != NULL) {
		freeAllNodes(H->next);
		freeNode(&H);
	}
}

// rotate_left()
// rotate the bits in an unsigned int
unsigned int rotate_left(unsigned int value, int shift) {
	int sizeInBits = 8 * sizeof(unsigned int);
	shift = shift & (sizeInBits - 1);
	if (shift == 0)
		return value;
	return (value << shift) | (value >> (sizeInBits - shift));
}
// pre_hash()
// turn a string into an unsigned int
unsigned int pre_hash(char* input) {
	unsigned int result = 0xBAE86554;
	while (*input) {
		result ^= *input++;
		result = rotate_left(result, 5);
	}
	return result;
}
// hash()
// turns a string into an int in the range 0 to tableSize-1
int hash(char* key) {
	return pre_hash(key) % tableSize;
}

int countChars(Dictionary D)
{
	Node N;

	int numChars = 0;
	for (int i = 0; i < tableSize; i++)
	{
		N = D->table[i];
		while (N != NULL)
		{
			numChars += strlen(N->key);
			numChars += strlen(N->val);
			N = N->next;
		}
	}
	numChars = numChars + (D->numPairs * 2);
	return numChars;
}
// Constructors-Destructors ---------------------------------------------------

Dictionary newDictionary() {
	Dictionary D = malloc(sizeof(DictionaryObj));
	D->numPairs = 0;
	D->table = calloc(tableSize, sizeof(Node));

	return D;
}

// freeDictionaryList()
// Destructor for the Dictionary ADT
void freeDictionary(Dictionary* pL) {
	if (pL != NULL && *pL != NULL) {
		makeEmpty(*pL);
		free(*pL);
		*pL = NULL;
	}
}

// ADT operations -------------------------------------------------------------

int size(Dictionary D)
{
	if (D == NULL) {
		fprintf(stderr,
			"Dictionary Error: size() called on NULL Dictionary reference\n");
		exit(EXIT_FAILURE);
	}

	return D->numPairs;
}

// lookup()
// If D contains a pair whose key matches argument k, then return the 
// corresponding value, otherwise return NULL.
char* lookup(Dictionary D, char* k)
{
	Node N;

	if (D == NULL) {
		fprintf(stderr,
			"Dictionary Error: lookup() called on NULL Dictionary reference\n");
		exit(EXIT_FAILURE);
	}

	int index = hash(k);
	N = D->table[index];

	while (N != NULL)
	{
		if (strcmp(N->key, k) == 0)
		{
			return N->val;
		}
		N = N->next;
	}

	return NULL;
}

// insert()
// Insert the pair (k,v) into D.
// Pre: lookup(D, k)==NULL (D does not contain a pair whose first member is k.)
void insert(Dictionary D, char* k, char* v) {
	Node N;
	int index = hash(k);

	if (D == NULL) {
		fprintf(stderr,
			"Dictionary Error: insert() called on NULL Dictionary reference\n");
		exit(EXIT_FAILURE);
	}

	if (lookup(D, k) == NULL)
	{
		N = newNode(k, v);
		//set the next pointer to the head
		N->next = D->table[index];
		//reset the head
		D->table[index] = N;
		D->numPairs++;
	}
}

// delete()
// Remove pair whose first member is the argument k from D.
// Pre: lookup(D,k)!=NULL (D contains a pair whose first member is k.)
void delete(Dictionary D, char* k)
{
	int index = hash(k);
	Node N = D->table[index];
	Node F = N->next;

	if (D == NULL)
	{
		fprintf(stderr,
			"Dictionary Error: delete() called on NULL Dictionary reference\n");
		exit(EXIT_FAILURE);
	}

	if(N != NULL)
	{
		//if the first node is the key node
		if (strcmp(N->key, k) == 0)
		{
			D->table[index] = F;
			N->next = NULL;
			freeNode(&N);
		}
		else
		{
			while (F != NULL)
			{
				if (strcmp(F->key, k) == 0)
				{
					N->next = F->next;
					break;
				}

				F = F->next;
				N = N->next;
			}

			F->next = NULL;
			freeNode(&F);
		}
		D->numPairs--;


	}
	else
	{
		freeNode(&N);
		D->table[index] = NULL;
		D->numPairs = 0;
	}

}

// makeEmpty()
// Reset D to the empty state, the empty set of pairs.
void makeEmpty(Dictionary D) {
	if (D == NULL) {
		fprintf(stderr,
			"Dictionary Error: makeEmpty() called on NULL Dictionary reference\n");
		exit(EXIT_FAILURE);
	}

	for (int i = 0; i < tableSize; i++) 
	{
		freeAllNodes(D->table[i]);
		D->table[i] = NULL;
		D->numPairs = 0;
	}
}

// Other Operations -----------------------------------------------------------

// DictionaryToString()
// Determines a text representation of the current state of Dictionary D. Each 
// (key, value) pair is represented as the chars in key, followed by a space,
// followed by the chars in value, followed by a newline '\n' char. The pairs 
// occur in alphabetical order by key. The function returns a pointer to a char 
// array, allocated from heap memory, containing the text representation 
// described above, followed by a terminating null '\0' char. It is the 
// responsibility of the calling function to free this memory.
char* DictionaryToString(Dictionary D)
{
	char* str = "";
	char* space = " ";
	char* newLine = "\n";
	char* end = "\0";
	int n;

	if (D == NULL) {
		fprintf(stderr,
			"Dictionary Error: calling DictionaryToString() on NULL Dictionary reference\n");
		exit(EXIT_FAILURE);
	}

	n = countChars(D);
	str = calloc(n + 1, sizeof(char));

	strcpy(str, "");
	for (int i = 0; i < tableSize; i++)
	{
		Node N = D->table[i];
		while (N != NULL)
		{
			strcat(str, N->key);
			strcat(str, space);
			strcat(str, N->val);
			strcat(str, newLine);
			if (N->next == NULL)
			{
				strcat(str, end);
			}
			N = N->next;

		}
	}
	return str;

	
}
