//-----------------------------------------------------------------------------
// Anton Kozintsev
// 1647521
// akozints@ucsc.edu
// IntegerQueue.c
// LinkedList based implementation of Integer Queue ADT in C
//-----------------------------------------------------------------------------
#include<stdlib.h>
#include<stdio.h>
#include<assert.h>
#include<string.h>
#include"IntegerQueue.h"

// Private Types and Functions ------------------------------------------------

// NodeObj
typedef struct NodeObj {
	int item;
	struct NodeObj* next;
	} NodeObj;

// Node
typedef NodeObj* Node;

// newNode()
// Constructor for Node type.
Node newNode(int x) {
	Node N = malloc(sizeof(NodeObj));
	assert(N != NULL);
	N->item = x;
	N->next = NULL;
	return(N);
}

// freeNode()
// Destructor for Node type
void freeNode(Node* pN) {
	if (pN != NULL && *pN != NULL) {
		free(*pN);
		*pN = NULL;
	}
}

typedef struct IntegerQueueObj {
	Node head;
	Node tail;
	int numItems;
}IntegerQueueObj;

int countChars(IntegerQueue Q)
{
	Node N = Q->head;
	Node start = Q->head;
	int count = 0;
	int temp;
	int numDigits = 0;

	while (N != NULL)
	{
		
	//numdigits makes sure we know how many actual numbers there 
		temp = N->item;
		//checks if the item is 0
		if (temp == 0)
		{
			numDigits++;
			count++;
		}
		else {
			while (temp != 0)
			{
				if (temp / 10 == 0)
				{
					numDigits++;
				}
				temp /= 10;
				count++;
			}
		}
		N = N->next;
	}

	//printf("The amount of numbers is: %d\n", numDigits);
	//printf("The count total amount of characters is: %d\n", count);

	return count + numDigits;
} 

// Constructors-Destructors ---------------------------------------------------

IntegerQueue newIntegerQueue(){
	IntegerQueue Q = malloc(sizeof(IntegerQueueObj));
	Q->head = NULL;
	Q->tail = NULL;
	Q->numItems = 0;
	return Q;
}

// freeIntegerQueue()
// Destructor for the Queue ADT
void freeIntegerQueue(IntegerQueue* pQ) {
	if (pQ != NULL && *pQ != NULL) {
		//dequeue all?
		free(*pQ);
		*pQ = NULL;
	}
}

// ADT operations -------------------------------------------------------------
// isEmpty()
// Returns 1 (true) if Queue Q is empty, 0 (false) otherwise.
int isEmpty(IntegerQueue Q) {
	if (Q == NULL) {
		fprintf(stderr,
			"IntegerQueue Error: calling isEmpty() on NULL IntegerQueue reference\n");
		exit(EXIT_FAILURE);
	}

	if (Q->numItems == 0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

// length()
// Returns the number of elements in Q
int length(IntegerQueue Q) {
	if (Q == NULL) {
		fprintf(stderr,
			"IntegerQueue Error: calling length() on NULL IntegerQueue reference\n");
		exit(EXIT_FAILURE);
	}

	return Q->numItems;

}

// enqueue()
// Inserts x at back of Q.
void enqueue(IntegerQueue Q, int x) {

	Node N = newNode(x);
	if (Q->head == NULL) { // Queue is empty
		Q->head = Q->tail = N;
	}
	else { // Queue is non-empty
		Q->tail->next = N;
		Q->tail = N;
	}
	Q->numItems++;
}

// dequeue()
// Deletes and returns the item at front of Q.
// Pre: !isEmpty()
int dequeue(IntegerQueue Q) {
	Node N;
	int x;

	if (Q == NULL) {
		fprintf(stderr,
			"IntegerQueue Error: calling dequeue() on NULL IntegerQueue reference\n");
		exit(EXIT_FAILURE);
	}

	if ((isEmpty(Q)))
	{
		fprintf(stderr,
			"IntegerQueue Error: calling dequeue() on empty IntegerQueue reference\n");
		exit(EXIT_FAILURE);
	}
	
	x = Q->head->item;
	N = Q->head;
	if (Q->head == Q->tail) {
		Q->head = Q->tail = NULL;
	}
	else {
		Q->head = Q->head->next;
	}

	Q->numItems--;
	freeNode(&N);
	return x;
}

// peek()
// Returns the item at front of Q.
// Pre: !isEmpty()
int peek(IntegerQueue Q) {

	int x;

	if (Q == NULL) {
		fprintf(stderr,
			"IntegerQueue Error: calling peek() on NULL IntegerQueue reference\n");
		exit(EXIT_FAILURE);
	}

	if ((isEmpty(Q)))
	{
		fprintf(stderr,
			"IntegerQueue Error: calling peek() on empty IntegerQueue reference\n");
		exit(EXIT_FAILURE);
	}

	x = Q->head->item;
	return x;
}

// dequeueAll()
// Resets Q to the empty state.
void dequeueAll(IntegerQueue Q) {

	if (Q == NULL) {
		fprintf(stderr,
			"IntegerQueue Error: calling dequeueAll() on NULL IntegerQueue reference\n");
		exit(EXIT_FAILURE);
	}

	Q->numItems = 0;
	Q->head = NULL;
	Q->tail = NULL;
}

// IntegerQueueToString()
// Determines a text representation of IntegerQueue Q. Returns a pointer to a 
// char array, allocated from heap memory, containing the integer sequence 
// represented by Q. The sequence is traversed from front to back, each integer
// is added to the string followed by a single space. The array is terminated 
// by a NULL '\n' character. It is the responsibility of the calling function to 
// free this heap memory
char* IntegerQueueToString(IntegerQueue Q) {

	char* str = "";
	char* space = " ";
	char* end = "\0";
	int n;
	int item;
	Node N = Q->head;

	if (Q == NULL) {
		fprintf(stderr,
			"IntegerQueue Error: calling IntegerQueueToString() on NULL IntegerQueue reference\n");
		exit(EXIT_FAILURE);
	}

	
	n = countChars(Q);
	str = calloc(n + 1, sizeof(char));

	char buffer[100];
	strcpy(str, "");
	while (N != NULL)
	{
		item = N->item;
		sprintf(buffer, "%d", item);
		strcat(str, buffer);
		strcat(str, space);

		/*
		if (N->next == NULL)
		{
			strcat(str, end);
		}
		*/
		N = N->next;
	}

	strcat(str, end);
	return str;
}

// equals()
// Returns true (1) if Q and R are matching sequences of integers, false (0) 
// otherwise.
int equals(IntegerQueue Q, IntegerQueue R)
{
	Node N = Q->head;
	Node M = R->head;

	if (Q == NULL || R==NULL) {
		fprintf(stderr,
			"IntegerQueue Error: calling equals() on NULL IntegerQueue reference\n");
		exit(EXIT_FAILURE);
	}

	if (R->numItems == Q->numItems)
	{
		while (N != NULL)
		{
			if (N->item != M->item)
			{
				return 0;
			}
			N = N->next;
			M = M->next;
		}
	}
	else
	{
		return 0;
	}

	return 1;


}