/*
Implementing my memoryallocation by using
	1.Technique of buddy allocator
	2.Using array of free lists for different stages. My memory buffer is of size 1024 so there are 10 stages i.e levels
	3.Using a list_entry for my stages having prev and next pointers,so as to create memory blocks and checking the necessary conditions to allocate
	  memory
	
	  

Buddy Allocator :
Memory buffer: 1024 bytes
Stages or Levels : 10 */


typedef struct listentry {
	 void *prev, *next;
}listentry;


void *freelist[10][512]; 



void *reference_head, *reference_tail, *memory_start, *memory_end, *memory_mid;

#define MAX_LEVEL 10 /* 2^10 = 1024 bytes */
#define blocksize(level) (1 << (level))
#define memory_buffer 1024
#define INDEX_OF_POINTER_IN_LEVEL(pointer,level,pointer2)  (((char *)(pointer) - (char *)(pointer2)) / (blocksize(level)))


listentry list[MAX_LEVEL];



void *allocate(unsigned int size);
void splitmemory(unsigned int size, unsigned int block_size, int i);
void creatememory(unsigned int size);
void *mymalloc(unsigned int size);
void initialisation();
void initialise_list(listentry *link);
void *findblockfromfreelist(int level);
void myfree(void *p, unsigned int size);
void deallocate(void *p, int index, int level);
void *mycalloc(int num, unsigned int size);
void *myrealloc(void *ptr, unsigned int previoussize, unsigned int size);
