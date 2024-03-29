#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "mymem.h"
#include <time.h>

/* The main structure for implementing memory allocation.
 * You may change this to fit your implementation.
 */

struct memoryList
{
  // doubly-linked list
  struct memoryList *last;
  struct memoryList *next;

  int size;            // How many bytes in this block?
  char alloc;          // 1 if this block is allocated,
                       // 0 if this block is free.
  void *ptr;           // location of block in memory pool.
};

strategies myStrategy = NotSet;    // Current strategy


size_t mySize;
void *myMemory = NULL;

static struct memoryList *head;
static struct memoryList *next;

// Define methods
void releaseMemory();
void initializeMemory(size_t);
struct memoryList* getBestFreeBlock(size_t);
struct memoryList* splitBlock(struct memoryList *currentBlock, size_t);
/* initmem must be called prior to mymalloc and myfree.

   initmem may be called more than once in a given exeuction;
   when this occurs, all memory you previously malloc'ed  *must* be freed,
   including any existing bookkeeping data.

   strategy must be one of the following:
		- "best" (best-fit)
		- "worst" (worst-fit)
		- "first" (first-fit)
		- "next" (next-fit)
   sz specifies the number of bytes that will be available, in total, for all mymalloc requests.
*/

void initmem(strategies strategy, size_t sz)
{
	myStrategy = strategy;

	/* all implementations will need an actual block of memory to use */
	mySize = sz;

	if (myMemory != NULL) free(myMemory); /* in case this is not the first time initmem2 is called */

	/* TODO: release any other memory you were using for bookkeeping when doing a re-initialization! */
	releaseMemory();

	myMemory = malloc(sz);
	/* TODO: Initialize memory management structure. */
	initializeMemory(sz);


}

void releaseMemory() {
	if (head != NULL) free(head);
	if (next != NULL) free(next);
}

void initializeMemory(size_t size) {	
	struct memoryList *current = malloc(sizeof(struct memoryList));// (struct memoryList *)
	current -> last = current;
    current -> next = current;
    current -> size = size;
    current -> alloc = 0;
    current -> ptr = myMemory;
    head = current;
    next = current;
}

/* Allocate a block of memory with the requested size.
 *  If the requested block is not available, mymalloc returns NULL.
 *  Otherwise, it returns a pointer to the newly allocated block.
 *  Restriction: requested >= 1 
 */

void *mymalloc(size_t requested)
{
	assert((int)myStrategy > 0);
	
	switch (myStrategy)
	  {
	  case NotSet: 
	            return NULL;
	  case First:
	            return NULL;
	  case Best: {
          struct memoryList *bestFreeBlock = getBestFreeBlock(requested);
          if (bestFreeBlock == NULL) return NULL;
          struct memoryList *allocatedBlock = splitBlock(bestFreeBlock, requested);
          next = bestFreeBlock->next;
          return bestFreeBlock->ptr;
      }
	  case Worst:
	            return NULL;
	  case Next:
	            return NULL;
	  }
	return NULL;
}

void* getNewBlockPointer(struct memoryList *current, size_t requested) {

}


struct memoryList* getBestFreeBlock(size_t size) {
	struct memoryList *bestBlock = NULL;
	struct memoryList *currentBlock = head;
	do {
		if (currentBlock->alloc == 0 && currentBlock->size >= size && 
			(bestBlock == NULL // Try here to put !bestBlock instead
			 || currentBlock->size < bestBlock-> size)) {
			bestBlock = currentBlock;
		}
		currentBlock = currentBlock->next;
	} while (currentBlock != head)
	    ;
	return bestBlock;
}

struct memoryList* splitBlock(struct memoryList *currentBlock, size_t size) {
	currentBlock -> alloc = 1;
	if (currentBlock-> size != size) {
		struct memoryList *newBlock = malloc(sizeof(struct memoryList));//Tail of node  // (struct memoryList *)
		newBlock -> size = currentBlock->size - size;
		currentBlock -> size = size;
		newBlock -> alloc = 0;
		newBlock -> ptr = currentBlock->ptr + size;

		/* Insert newBlock into doubly linked list */

		currentBlock -> next->last = newBlock;
		newBlock -> next = currentBlock->next;
		newBlock -> last = currentBlock;
		currentBlock -> next = newBlock;
		return newBlock;
	}
	currentBlock->size = size;
	return NULL;
}

/* Frees a block of memory previously allocated by mymalloc. */
void myfree(void *block) {
    struct memoryList *currentBlock = head;
    do {
        if (currentBlock->ptr == block)
            currentBlock->alloc = 0;
        currentBlock = currentBlock->next;
    } while (currentBlock != head)
            ;
}

/****** Memory status/property functions ******
 * Implement these functions.
 * Note that when refered to "memory" here, it is meant that the 
 * memory pool this module manages via initmem/mymalloc/myfree. 
 */

/* Get the number of contiguous areas of free space in memory. */
int mem_holes() {
    int countOfFreeBlocks = 0;
    struct memoryList *currentBlock = head;
    do {
        if (currentBlock->alloc == 0)
            countOfFreeBlocks++;
        currentBlock = currentBlock->next;
    } while (currentBlock != head)
        ;
    return countOfFreeBlocks;
}

/* Get the number of bytes allocated */
int mem_allocated() {
    int numberOfBytes = 0;
    struct memoryList *currentBlock = head;
    do {
        if (currentBlock->alloc == 1)
            numberOfBytes += currentBlock->size;
        currentBlock = currentBlock->next;
    } while (currentBlock != head)
            ;
    return numberOfBytes;
}

/* Number of non-allocated bytes */
int mem_free()
{
    int numberOfBytes = 0;
    struct memoryList *currentBlock = head;
    do {
        if (currentBlock->alloc == 0)
            numberOfBytes += currentBlock->size;
        currentBlock = currentBlock->next;
    } while (currentBlock != head)
            ;
    return numberOfBytes;
}

/* Number of bytes in the largest contiguous area of unallocated memory */
int mem_largest_free()
{
    int largestNumberOfByte = 0;
    struct memoryList *currentBlock = head;
    do {
        if (largestNumberOfByte < currentBlock->size && currentBlock->alloc == 0)
            largestNumberOfByte = currentBlock->size;
        currentBlock = currentBlock->next;
    } while (currentBlock != head)
            ;
    return largestNumberOfByte;
}
// TODO: Smaller or equal not just smaller
/* Number of free blocks smaller than "size" bytes. */
int mem_small_free(int size)
{
    int countOfFreeBlocks = 0;
    struct memoryList *currentBlock = head;
    do {
        if (currentBlock->alloc == 0 && currentBlock->size <= size)
            countOfFreeBlocks++;
        currentBlock = currentBlock->next;
    } while (currentBlock != head)
            ;
    return countOfFreeBlocks;
	return 0;
}

char mem_is_alloc(void *ptr)
{
    struct memoryList *currentBlock = head;
    do {
        if (currentBlock->ptr == ptr)
            return currentBlock->alloc;
        currentBlock = currentBlock->next;
    } while (currentBlock != head)
            ;
    return  0;
}

/* 
 * Feel free to use these functions, but do not modify them.  
 * The test code uses them, but you may find them useful.
 */


//Returns a pointer to the memory pool.
void *mem_pool()
{
	return myMemory;
}

// Returns the total number of bytes in the memory pool. */
int mem_total()
{
	return mySize;
}


// Get string name for a strategy. 
char *strategy_name(strategies strategy)
{
	switch (strategy)
	{
		case Best:
			return "best";
		case Worst:
			return "worst";
		case First:
			return "first";
		case Next:
			return "next";
		default:
			return "unknown";
	}
}

// Get strategy from name.
strategies strategyFromString(char * strategy)
{
	if (!strcmp(strategy,"best"))
	{
		return Best;
	}
	else if (!strcmp(strategy,"worst"))
	{
		return Worst;
	}
	else if (!strcmp(strategy,"first"))
	{
		return First;
	}
	else if (!strcmp(strategy,"next"))
	{
		return Next;
	}
	else
	{
		return 0;
	}
}


/* 
 * These functions are for you to modify however you see fit.  These will not
 * be used in tests, but you may find them useful for debugging.
 */

void print(struct memoryList *current, int index) {
    printf("bytes: %d, allocation status: %i, index: %i\n", current->size, current->alloc, index);
    if (current->next == head) return;
    print(current->next, index + 1);
}

/* Use this function to print out the current contents of memory. */
void print_memory()
{
    print(head, 0);
}

/* Use this function to track memory allocation performance.  
 * This function does not depend on your implementation, 
 * but on the functions you wrote above.
 */ 
void print_memory_status()
{
	printf("%d out of %d bytes allocated.\n",mem_allocated(),mem_total());
	printf("%d bytes are free in %d holes; maximum allocatable block is %d bytes.\n",mem_free(),mem_holes(),mem_largest_free());
	printf("Average hole size is %f.\n\n",((float)mem_free())/mem_holes());
}

/* Use this function to see what happens when your malloc and free
 * implementations are called.  Run "mem -try <args>" to call this function.
 * We have given you a simple example to start.
 */
void try_mymem(int argc, char **argv) {
        strategies strat;
	void *a, *b, *c, *d, *e;
	if(argc > 1)
	  strat = strategyFromString(argv[1]);
	else
	  strat = First;
	
	
	/* A simple example.  
	   Each algorithm should produce a different layout. */
	
	initmem(strat,500);
	
	a = mymalloc(100);
	b = mymalloc(100);
	c = mymalloc(100);
	myfree(b);
	d = mymalloc(50);
	myfree(a);
	e = mymalloc(25);
	
	print_memory();
	print_memory_status();
	
}

int main() {

}