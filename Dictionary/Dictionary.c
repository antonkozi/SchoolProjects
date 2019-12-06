//-----------------------------------------------------------------------------
// Name: Anton Kozintsev
// Email: akozints@ucsc.edu
// ID: 1647521
// Dictionary.c
// Linked List implementation of the Dictionary ADT.
//-----------------------------------------------------------------------------
#include<stdlib.h>
#include<stdio.h>
#include<assert.h>
#include<string.h>
#include"Dictionary.h"


// Private Types and Functions ------------------------------------------------

// NodeObj type
typedef struct NodeObj {
	char* key;
	char* val;
	struct NodeObj* next;
} NodeObj;

// Node type
typedef NodeObj* Node;

// DictionaryObj type
typedef struct DictionaryObj {
	Node head;         // pointer to first Node in list
	Node tail;         // pointer to the last Node in list
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
// findKey()
// returns a reference to the Node at position index in list headed by Head
Node findKey(Dictionary D, char* k) {
	Node N = D->head;

	while(N != NULL)
	{
		if (strcmp(N->key, k) == 0)
		{
			break;
		}
		N = N->next;
	}
	return N;
}

//countChars()
//counts the number of characters in the text representation of D
int countChars(Dictionary D)
{
	int numChars = 0;
	Node N = D->head;
	while (N!= NULL)
	{
		numChars += strlen(N->key);
		numChars += strlen(N->val);
		N = N->next;
	}
	numChars = numChars + (D->numPairs * 2);
	//numChars++;
	return numChars;
}

// Constructors-Destructors ---------------------------------------------------

// newDictionary()
// Constructor for the Dictionary ADT
Dictionary newDictionary() {
	Dictionary D = malloc(sizeof(DictionaryObj));
	D->head = NULL;
	D->tail = NULL;
	D->numPairs = 0;

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

/*If 𝐷 contains a pair whose key matches argument 𝑘, then return the corresponding value, otherwise
return NULL.
*/
char* lookup(Dictionary D, char* k)
{
	Node N;
	if (D == NULL) {
		fprintf(stderr,
			"Dictionary Error: lookup() called on NULL Dictionary reference\n");
		exit(EXIT_FAILURE);
	}

	if (findKey(D, k) != NULL)
	{
		N = findKey(D, k);
		return N->val;
	}else return NULL;

	//N = findKey(D, k);
	//return (N == NULL ? NULL : N->val);
	
}

/*Insert the pair(𝑘, 𝑣) into 𝐷.
Pre : lookup(𝐷, 𝑘) == NULL. (𝐷 does not contain a pair whose first member is 𝑘.)*/
void insert(Dictionary D, char* k, char* v)
{
	
	Node T;

	if (D == NULL) {
		fprintf(stderr,
			"Dictionary Error: insert() called on NULL Dictionary reference\n");
		exit(EXIT_FAILURE);
	}

	if (lookup(D, k) == NULL)
	{

		T = newNode(k, v);
		if (D->numPairs == 0)
		{
			D->head = T;
			D->tail = D->head;
			//head = tail->next?
			//D->tail->next = NULL;
		}
		else 
		{
		
			D->tail->next = T;
			D->tail = D->tail->next;
			D->tail->next = NULL;
			
		}
		D->numPairs++;
	}

}

//Remove pair whose first member is the argument 𝑘 from 𝐷.
	//Pre : lookup(𝐷, 𝑘) ≠ NULL. (𝐷 contains a pair whose first member is 𝑘.)
void delete(Dictionary D, char* k)
{
	Node N = D->head;
	Node F = N->next;

	if (D == NULL) 
	{
		fprintf(stderr,
			"Dictionary Error: delete() called on NULL Dictionary reference\n");
		exit(EXIT_FAILURE);
	}


	if (lookup(D, k) != NULL)
	{
		
		
			if (F != NULL)
			{
				//if the first node is the key node
				if (strcmp(N->key, k) == 0)
				{
					D->head = F;
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
				D->head = NULL;
				D->tail = NULL;
				D->numPairs = 0;
			}
		
	}
}


//Reset 𝐷 to the empty state, the empty set of pairs.

void makeEmpty(Dictionary D)
{
    if (D == NULL) {
		fprintf(stderr,
			"Dictionary Error: makeEmpty() called on NULL Dictionary reference\n");
		exit(EXIT_FAILURE);
	}

	freeAllNodes(D->head);
	D->head = NULL;
	D->numPairs = 0;
}


// Determines a text representation of the current state of Dictionary D.Each
// (key, value) pair is represented as the chars in key, followed by a space,
// followed by the chars in value, followed by a newline '\n' char. The pairs 
// occur in the same order they were inserted into D. The function returns a
// pointer to a char array, allocated from heap memory, containing the text  
// representation described above, followed by a terminating null '\0' char. 
// It is the responsibility of the calling function to free this memory.

char* DictionaryToString(Dictionary D) {

	char* str = "";
	char* space = " ";
	char* newLine = "\n";
	char* end = "\0";
	int n;

	Node N = D->head;

	if (D == NULL) {
		fprintf(stderr,
			"Dictionary Error: calling DictionaryToString() on NULL Dictionary reference\n");
		exit(EXIT_FAILURE);
	}

	n = countChars(D);
	str = calloc(n + 1, sizeof(char));

	strcpy(str, "");
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
	return str;

}

