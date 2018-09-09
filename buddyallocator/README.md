MIS:111608039
Name: KUKREJA VINAY KUMAR GIRDHARI
TITLE: MEMORYALLOCATION USING THE CONCEPT OF BUDDY ALLOCATION

Implementing my memoryallocation by using
    1.Technique of buddy allocator
    2.Using array of free lists for different stages. My memory buffer is of size 1024 so there are 10 stages i.e levels
    3.Using a list_entry for my stages having prev and next pointers,so as to create memory blocks and checking the necessary conditions to allocate
      memory

Buddy Allocator :
Memory buffer: 1024 bytes
Stages or Levels : 10

How it works: 
ALLOCATING : My program first calculate the size of the memory block to be allocated for the size requested by the program. If there is not any available free block then 
it searches for the memory block using the list_entry for the required stage. If the memory block of that size is not available then it divides the memory block of 
next availble higher level into two buddies out of which one buddy is divided by 2 till the memory block of that size is obtained.

FREEING: While freeing, the program first calculate the index of pointer at that level and then accordingly if index is even or odd finds its buddies. If buddy is avaialble it
coalesce the two buddies to create a bigger memory block and then depending on the index and level of memory block freelist is pointed to the pointer to be freed. 
