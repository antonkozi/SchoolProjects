//-----------------------------------------------------------------------------
// Name: Anton Kozintsev
// Email: akozints@ucsc.edu
// ID: 1647521
// DictionaryTest
// A test of the dictionary ADT
//-----------------------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"Dictionary.h"


int main() {
	Dictionary D;
	char* str;
	char* v;
	char* k = calloc(100, sizeof(char));

	// create a Dictionary and some pairs into it
	D = newDictionary();
	insert(D, "Snow", "Jon");
	insert(D, "Stark", "Arya");
	insert(D, "Lannister", "Jamie");
	insert(D, "Targareyan", "Daenerys");
	//insert(D, "Stark", "Sansa");  does not work due to having the same key

	// print out the Dictionary
	str = DictionaryToString(D);
	printf("%s\n", str);
	free(str);

	// test lookup()
	v = lookup(D, "Snow");
	printf("%s", v);
	printf("\n");
	v = lookup(D, "Stark");
	printf("%s", v);
	printf("\n");
	//The key Tully does not exist
	v = lookup(D, "Tully");
	printf("v = %s", v);
	printf("\n");

	

	// delete some pairs
	delete(D, "Targareyan");
	delete(D, "Lannister");
	// delete(D, "Lannister"); causes error since it was already deleted

	// print out the Dictionary
	str = DictionaryToString(D);
	printf("%s\n", str);
	free(str);

	

	// check size
	printf("size(D) = %d\n", size(D));
	printf("\n");

	//delete all the pairs
	delete(D, "Stark");
	delete(D, "Snow");

	//check size again
	printf("size(D) = %d\n", size(D));
	printf("\n");

	//insert the pairs back
	insert(D, "Snow", "Jon");
	insert(D, "Stark", "Arya");
	insert(D, "Lannister", "Jamie");
	insert(D, "Targareyan", "Daenerys");

	//print dictionary
	str = DictionaryToString(D);
	printf("%s\n", str);
	free(str);

	// make D empty, check size, print it out
	makeEmpty(D);
	printf("size(D) = %d\n", size(D));
	str = DictionaryToString(D);
	printf("%s\n", str);
	free(str);

	// free everything
	free(k);
	freeDictionary(&D);

	return EXIT_SUCCESS;
}
