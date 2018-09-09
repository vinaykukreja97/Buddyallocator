#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "memory.h"



int main() {
	 void *ptr[7];
	 
	 ptr[0] = (int *)mymalloc(0);
	 if(ptr[0] == NULL) {
			printf("test for size 0 successful\n");
	 }
	 else {
			printf("test for size 0 was unsuccessful\n");

	 }

	 /* test to check if various data types and their respective sizes can get allocated */

	ptr[0] = (short *)mymalloc(2);
	if(ptr[0] != NULL) {
			printf("test for short* successful\n");
	}
	else {
			printf("test for short* was unsuccessful\n");

	}
	myfree(ptr[0], 2);


	ptr[1] = (int *)mymalloc(4);
	if(ptr[1] != NULL) {
			printf("test for int* successful\n");
	}
	else {
			printf("test for int* was unsuccessful\n");

	}
	myfree(ptr[1], 4);

	ptr[2] = (long *)mymalloc(4);
	if(ptr[2] != NULL) {
			printf("test for long* successful\n");
	}
	else {
			printf("test for long* was unsuccessful\n");

	}
	myfree(ptr[2], 4);

	ptr[3] = (float *)mymalloc(4);
	if(ptr[3] != NULL) {
			printf("test for float* successful\n");
	}
	else {
			printf("test for float* was unsuccessful\n");

	}
	myfree(ptr[3], 4);


	ptr[4] = (double *)mymalloc(8);
	if(ptr[4] != NULL) {
			printf("test for double* successful\n");
	}
	else {
			printf("test for double* was unsuccessful\n");

	}
	myfree(ptr[4], 8);

	ptr[5] = (long double *)mymalloc(16);
	if(ptr[5] != NULL) {
			printf("test for long double* successful\n");
	}
	else {
			printf("test for long double* was unsuccessful\n");

	}
	myfree(ptr[5], 16);

	ptr[6] = (char *)mymalloc(1);

	if(ptr[6] != NULL) {
			printf("test for char* successful\n");
	}
	else {
			printf("test for char* was unsuccessful\n");

	 }
	myfree(ptr[6], 1);

	/*test for int  pointer */
	int i, *_intpointer, *_reallocintpointer;

	for(i = 0; i < 100; i++) {
		_intpointer = mymalloc(4);
		*(_intpointer) = i;
		myfree(_intpointer, 4); 
	}

	_intpointer = mymalloc(100 * 4);
	for(i = 0; i < 100; i++) {
		*(_intpointer + i) = i;
		
	}
	myfree(_intpointer, 4 * 100);

	_intpointer = mycalloc(100, 4);

	for(i = 0; i < 100; i++) {
		*(_intpointer + i) = i;
		
	}

	myfree(_intpointer, 4 * 100);

	_reallocintpointer = myrealloc(_intpointer, 4 * 100, 4 * 110);

	for(i = 0; i < 110; i++) {
		*(_reallocintpointer + i) = i;
	
	}

	myfree(_reallocintpointer, 4 * 110);


	/*test for char pointer */

	char *ch, *_reallocchpointer;
	for(i = 0; i < 100; i++) {
		ch = mymalloc(1);
		*ch = i;
		myfree(ch, 1);
	}

	ch = mycalloc(100, 1);

	for(i = 0; i < 100; i++) {
		
		*(ch + i) = i;
		
	}

	myfree(ch, 1 * 100);

	_reallocchpointer = myrealloc(ch, 1 * 100, 1 * 110);

	for(i = 0; i < 110; i++) {
		*(_reallocchpointer + i) = i;
	
	}
	myfree(_reallocchpointer, 1 * 110);


	/* random */

	void *random, *randomrealloc;

	random = (int *)mymalloc(140);
	if(random != NULL) {
		printf("test for any size(malloc):success\n");
	}
	else {
		printf("test for any size(malloc):failed\n");
	}

	myfree(random, 140);

	random = mycalloc(10, 12);
	if(random != NULL) {
		printf("test for any size(calloc):success\n");
	}
	else {
		printf("test for any size(calloc):failed\n");
	}

	randomrealloc = myrealloc(random, 120, 180);
	if(random != NULL) {
		printf("test for any size(realloc):success\n");
	}
	else {
		printf("test for any size(realloc):failed\n");
	}
	myfree(randomrealloc, 180);


	/* to check if calloc is initialised */

	_intpointer = mycalloc(5, 4);
	printf("test to check if calloc is initialised or not for number of elements\n");
	for(i = 0; i < 5; i++) {
		printf("%d\n", *(_intpointer + i));
	}

	myfree(_intpointer, 5 * 4);

	
	
	return 0;

}
