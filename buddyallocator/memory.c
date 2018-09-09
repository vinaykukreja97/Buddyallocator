/*
Implementing my memoryallocation by using
	1.Technique of buddy allocator
	2.Using array of free lists for different stages. My memory buffer is of size 1024 so there are 10 stages i.e levels
	3.Using a list_entry for my stages having prev and next pointers,so as to create memory blocks and checking the necessary conditions to allocate
	  memory
	
	  

Buddy Allocator :
Memory buffer: 1024 bytes
Stages or Levels : 10 */




#include <errno.h>
#include <unistd.h>
#include "memory.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h> 
#include <string.h>

/*initialisation function uses sbrk() to allocate memory_buffer(1024) and also it initailises the list using initialise_list function and 
also it inialises the free lists to NULL
if failed it returns nothing and exit */

void initialisation() {
	int i = 0, j;
	

	
	reference_head = sbrk(0);
	if(reference_head == (void *)-1) {          
			errno = ENOMEM;
			perror("no extra space\n");
			exit(0);

	}

	memory_start = reference_head;

	if(sbrk(1024) == (void *)-1) {          
		errno = ENOMEM;
		perror("no extra space\n");
		
		exit(0);
	}

	reference_tail = sbrk(0);

	if(reference_tail == (void *)-1) {          
		errno = ENOMEM;
		perror("no extra space\n");
		
		exit(0);
	}

	


	for(i = 0; i < MAX_LEVEL; i++) {
		initialise_list(&list[i]);
	}

	for(i = 0; i < 10; i++) {
		for(j = 0; j < 512; j++) {
			freelist[i][j] = NULL;
		}
	}
	return;
	
}

/*It takes listentry pointer and initialises its prev and next elements to NULL */
 
void initialise_list(listentry *list) {
	list -> prev = NULL;
	list -> next = NULL;
	return;
}


/*It takes the level i.e stage in my memory_buffer as an argument and finds if there is any free memory
block in that stage and returns it. If not found it returns NULL */

void *findblockfromfreelist(int level) {
	int i;	
	void *tmp;
	
	for(i = 0; i < 512; i++) {
		if(freelist[level][i] != NULL) {
			tmp = freelist[level][i];
			freelist[level][i] = NULL;
			break;
			
		}

		else {
			continue;
		}

	}

	if(i == 512) {
		tmp = NULL;
	}
	return tmp;
}





/*allocate function finds the correct memory block and if its not there it splits the higher level memory block  makes buddies and 
 allocates the memory block for given size
 and returns the correct memory block allocated and if failed returns NULL */ 
void *allocate(unsigned int size) {
	int  i;
	void *tmp;

	if(size > 1024) {
		creatememory(size);
		tmp = reference_head;

		reference_head = sbrk(0);

		if(reference_head == (void *)-1) {          
			errno = ENOMEM;
			perror("no extra space\n");
			exit(0);

		}

		if(sbrk(1024) == (void *)-1) {          
		errno = ENOMEM;
		perror("no extra space\n");
		
		exit(0);
		}

		reference_tail = sbrk(0);

		if(reference_tail == (void *)-1) {          
			errno = ENOMEM;
			perror("no extra space\n");
		
			exit(0);
		}
		
 		return tmp;
	}


	else if(size == 1024) {
		tmp = reference_head;
		reference_head =  reference_tail;
		if(sbrk(1024) == (void *)-1) {          
			errno = ENOMEM;
			perror("no extra space\n");
		
			exit(0);
		}

		reference_tail = sbrk(0);

		if(reference_tail == (void *)-1) {          
			errno = ENOMEM;
			perror("no extra space\n");
		
			exit(0);
		}
		return tmp;
	}


	for(i = 0; blocksize(i) < size; i++);

	if(size < 1024) {
		if(list[i].prev != NULL) {
			tmp = list[i].prev;   /*block is available */
			list[i].prev = NULL;
			return tmp;
		}	
		else if (list[i].prev == NULL && list[i].next == NULL) {
				tmp = findblockfromfreelist(i);
				if(tmp != NULL) {
					return tmp;
			
				}	
			
				else {
					
					splitmemory(size,(blocksize(i + 1)), (i + 1)); /*block is not available */
					tmp = allocate(size);
				}
		}
		else if(list[i].prev == NULL && list[i].next != NULL) {
			tmp = list[i].next;
								/*other buddy is available */
			list[i].next = NULL;
		}				
	
	}

		return tmp;
	
}


/*It takes size, block_size and  level i.e stage of memeory_buffer as arguments and it splits memory of higher level and makes buddies by checking the necessary
conditions and calling own function recursively.
If there is no memory block to split it creates memory by calling the creatememory function 
It also checks if the  memory chunk of 1024 bytes that we obtained is fully used or not*/ 

void splitmemory(unsigned int size,unsigned int block_size, int i) {
	void *tmp;
	if(list[i].prev != NULL) {
		tmp = list[i].prev;
		list[i - 1].prev = tmp;
		list[i - 1].next = (void *)((char *)tmp + blocksize(i - 1));
		list[i].prev = list[i].next;
		list[i].next = NULL;
		return;
	}

	else if(list[i].prev == NULL && i != 10) {

		splitmemory(size, blocksize(i + 1), i + 1);
		return;

	}

	
	

	else if(list[i].prev == NULL && i == 10) {  /*when all the stages are full */
		
		creatememory(size);
		tmp = reference_head;

		reference_head = sbrk(0);
		if(reference_head == (void *)-1) {          
			errno = ENOMEM;
			perror("no extra space\n");
			
			exit(0);

		}
	
		if(sbrk(1024) == (void *)-1) {          
			errno = ENOMEM;
			perror("no extra space\n");
			
			exit(0);

		}	

		reference_tail = sbrk(0);

		if(reference_tail == (void *)-1) {          
			errno = ENOMEM;
			perror("no extra space\n");
			
			exit(0);

		}
	}
												
	return;
	

}
	 
/* It takes size as an argument and it creates memory till it find the correct memory block of power of 2*/	
void creatememory(unsigned int size) {
	int diff, i, no;
	void *p;
	p = reference_tail;	
	diff =  ((char*)p - (char*)reference_head) / 2;
	int z = 9;
	
	if(size > 1024) {
		for(i = 0; blocksize(i) < size; i++);
			no = i % 10;
			
			if(sbrk(1024 * no) == (void *)-1) {          
				errno = ENOMEM;
				perror("no extra space\n");
				exit(0);
			}	
			reference_tail = sbrk(0);

			if(reference_tail == (void *)-1) {          
				errno = ENOMEM;
				perror("no extra space\n");
			
				exit(0);
			}

			return;


	}

		
		while(diff > size) {
			list[z].prev = (void*)((char*)p - diff) ;
			list[z].next = NULL;
			z--;
			p = (void*)((char*)p - diff);
			diff =  ((char*)p - (char*)reference_head) / 2;
		}


		if(diff < size) {
			if(z != 9) {
				list[z + 1].next = list[z + 1].prev;
				list[z + 1].prev =  (void*)((char*)list[z + 1].prev - blocksize(z + 1));
				
			}
			else {
				list[z].next = (void*)((char*)p- diff);
				list[z].prev = (void*)((char*)list[z].prev - blocksize(z));
			}
		}

		else if(diff == size) {
				list[z].next = (void*)((char*)p - blocksize(z));
				list[z].prev = (void*)((char*)list[z].next - blocksize(z));
				
		}

	return;
}

	


	
/*It takes size as argument and checks various possibilities according to my size of memory_buffer and returns the pointer pointing
to that memory block in which the size to be allocated is found. It uses the function allocate() to find the correct memory block and if not found 
it return NULL */

void *mymalloc(unsigned int size) {
	void *tmp = NULL;
	static int flag = 0;

	if(flag == 0) {
		initialisation();
		flag = 1;
	}

	if(size == 0) {
		tmp = NULL;
	}

	else if(size > 0) {
		tmp = allocate(size);
	}	


	return tmp;



}

/*This function takes the pointer to be freed and the size that the pointer holds as arguments. It uses the function
deallocate to make the pointer free */ 
void myfree(void *p, unsigned int size) {
	int i, index, j;

	for(i = 0; blocksize(i) < size; i++);

	if(i < 10) {
		for(j = 0; j < 512; j++) {
			if(freelist[i][j] == p) { /*first checks if the pointer was allocated from freelist and if it is then it frees from it i.e make NULL*/
				freelist[i][j] = NULL;
				p = NULL;
				return;
			}
		}
	}
	
	else if(i > 10) {
		return;
	}

	index  = INDEX_OF_POINTER_IN_LEVEL(p, i, memory_start);
	deallocate(p, index, i);
	return;
} 



/*It takes the pointer to be freed, index of pointer and the level i.e the stage as its arguments.
  It checks if there is buddy of that memory block so that it can  coalesce it by calling this function recursively
  and if buddy is not there then freelists of level and the index points to it. */ 
void deallocate(void *p, int index, int level) {
	int index2;
																		
	if(index % 2 == 0) {											/*that means the index are 0, 2, 4 ... so their buddies will be at odd 
																		positions, therefore to check if buddy is available or not we increment index by 1 */
			if(freelist[level][index + 1] == NULL) { /*buddy not found */  
				
				freelist[level][index] = p;
				return;
			}
			else if(!freelist[level][index + 1]) {
				
				index2 = INDEX_OF_POINTER_IN_LEVEL(p, level + 1, memory_start);
				deallocate(p, index2, level + 1);
				return;
			}
	}

	else  if(index % 2 == 1) {                                       /*that means the index are 1, 3, 5 ... so their buddies will be at even 
																		positions, therefore to check if buddy is available or not we decrement index by 1 */
		if(freelist[level][index - 1] == NULL) { /*buddy not found */
			freelist[level][index] = p;
			return;
		}

		else if(!freelist[level][index - 1]) {
			index2 = INDEX_OF_POINTER_IN_LEVEL(p, level + 1, memory_start);
			deallocate(p, index2, level + 1);
			return;
		}

	}

}

/*This functions takes the number of memory block and the size of memory block to be allocated and 
uses the malloc function to allocate  
returns the pointer pointing to the requied memory block
and if failed returns NULL*/
void *mycalloc(int num, unsigned int size) {
	void *tmp;
	int i;

	tmp = mymalloc(num * size);

	for(i = 0; i < num; i++) {
		*(int *)(tmp + i) = 0;
	}

	if(tmp ==  NULL) {
		return NULL;
	}

	return tmp;
}

/*This function takes the pointer to be reallocated, previoussize it holds, and new size 
uses mymalloc and myfree function to allocate the required size
returns the reallocated memory if success and if it fails it returns NULL */

void *myrealloc(void *ptr, unsigned int previoussize, unsigned int size) {
	void *tmp;

	if(size == 0) {
		return NULL;
	}

	if(size <= previoussize) {
		return ptr;
	}

	else {

		tmp = mymalloc(size);
		bcopy(ptr, tmp, size);
		myfree(ptr, previoussize);
		
	}

	return tmp;

}
