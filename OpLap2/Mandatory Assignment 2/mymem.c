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
    current -> ptr = mymemory;
    head = current;
    next = current;
}

/* allocate a block of memory with the requested size.
 *  if the requested block is not available, mymalloc returns null.
 *  otherwise, it returns a pointer to the newly allocated block.
 *  restriction: requested >= 1
 */

void *mymalloc(size_t requested)
{
	assert((int)mystrategy > 0);

	switch (mystrategy)
	  {
	  case notset:
	            return null;
	  case first:
	            return null;
	  case best: {
          struct memorylist *bestfreeblock = getbestfreeblock(requested);
          if (bestfreeblock == null) return null;
          struct memorylist *allocatedblock = splitblock(bestfreeblock, requested);
          next = bestfreeblock->next;
          return bestfreeblock->ptr;
      }
	  case worst:
	            return null;
	  case next:
	            return null;
	  }
	return null;
}

void* getnewblockpointer(struct memorylist *current, size_t requested) {

}


struct memorylist* getbestfreeblock(size_t size) {
	struct memorylist *bestblock = null;
	struct memorylist *currentblock = head;
	do {
		if (currentblock->alloc == 0 && currentblock->size >= size &&
			(bestblock == NULL // try here to put !bestblock instead
			 || currentblock->size < bestblock-> size)) {
			bestblock = currentblock;
		}
		currentblock = currentblock->next;
	} while (currentblock != head);
	return bestblock;
}

struct memorylist* splitblock(struct memorylist *currentblock, size_t size) {
	currentblock -> alloc = 1;
	if (currentblock-> size != size) {
		struct memorylist *newblock = malloc(sizeof(struct memorylist));//tail of node  // (struct memorylist *)
		newblock -> size = currentblock->size - size;
		currentblock -> size = size;
		newblock -> alloc = 0;
		newblock -> ptr = currentblock->ptr + size;

		/* insert newblock into doubly linked list */

		currentblock -> next->last = newblock;
		newblock -> next = currentblock->next;
		newblock -> last = currentblock;
		currentblock -> next = newblock;
		return newblock;
	}
	currentblock->size = size;
	return null;
}

/* frees a block of memory previously allocated by mymalloc. */
void myfree(void *block) {
    struct memoryList *currentBlock = head;
    do {
        if (currentBlock->ptr == block)
            currentBlock->alloc = 0;
        currentBlock = currentBlock->next;
    } while (currentBlock != head)
            ;
}

/****** memory status/property functions ******
 * implement these functions.
 * note that when refered to "memory" here, it is meant that the
 * memory pool this module manages via initmem/mymalloc/myfree.
 */

/* get the number of contiguous areas of free space in memory. */
int mem_holes() {
    int countoffreeblocks = 0;
    struct memorylist *currentblock = head;
    do {
        if (currentblock->alloc == 0)
            countoffreeblocks++;
        currentblock = currentblock->next;
    } while (currentblock != head)
        ;
    return countoffreeblocks;
}

/* get the number of bytes allocated */
int mem_allocated() {
    int numberofbytes = 0;
    struct memorylist *currentblock = head;
    do {
        if (currentblock->alloc == 1)
            numberofbytes += currentblock->size;
        currentblock = currentblock->next;
    } while (currentblock != head)
            ;
    return numberofbytes;
}

/* number of non-allocated bytes */
int mem_free()
{
    int numberofbytes = 0;
    struct memorylist *currentblock = head;
    do {
        if (currentblock->alloc == 0)
            numberofbytes += currentblock->size;
        currentblock = currentblock->next;
    } while (currentblock != head)
            ;
    return numberofbytes;
}

/* number of bytes in the largest contiguous area of unallocated memory */
int mem_largest_free()
{
    int largestnumberofbyte = 0;
    struct memorylist *currentblock = head;
    do {
        if (largestnumberofbyte < currentblock->size && currentblock->alloc == 0)
            largestnumberofbyte = currentblock->size;
        currentblock = currentblock->next;
    } while (currentblock != head)
            ;
    return largestnumberofbyte;
}

/* number of free blocks smaller than "size" bytes. */
int mem_small_free(int size)
{
    int countoffreeblocks = 0;
    struct memorylist *currentblock = head;
    do {
        if (currentblock->alloc == 0 && currentblock->size <= size)
            countoffreeblocks++;
        currentblock = currentblock->next;
    } while (currentblock != head)
            ;
    return countoffreeblocks;
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
 * feel free to use these functions, but do not modify them.
 * the test code uses them, but you may find them useful.
 */


//returns a pointer to the memory pool.
void *mem_pool()
{
	return mymemory;
}

// returns the total number of bytes in the memory pool. */
int mem_total()
{
	return mysize;
}


// get string name for a strategy.
char *strategy_name(strategies strategy)
{
	switch (strategy)
	{
		case best:
			return "best";
		case worst:
			return "worst";
		case first:
			return "first";
		case next:
			return "next";
		default:
			return "unknown";
	}
}

// get strategy from name.
strategies strategyfromstring(char * strategy)
{
	if (!strcmp(strategy,"best"))
	{
		return best;
	}
	else if (!strcmp(strategy,"worst"))
	{
		return worst;
	}
	else if (!strcmp(strategy,"first"))
	{
		return first;
	}
	else if (!strcmp(strategy,"next"))
	{
		return next;
	}
	else
	{
		return 0;
	}
}


/*
 * these functions are for you to modify however you see fit.  these will not
 * be used in tests, but you may find them useful for debugging.
 */

void print(struct memorylist *current, int index) {
    printf("bytes: %d, allocation status: %i, index: %i\n", current->size, current->alloc, index);
    if (current->next == head) return;
    print(current->next, index + 1);
}

/* use this function to print out the current contents of memory. */
void print_memory()
{
    print(head, 0);
}

/* use this function to track memory allocation performance.
 * this function does not depend on your implementation,
 * but on the functions you wrote above.
 */
void print_memory_status()
{
	printf("%d out of %d bytes allocated.\n",mem_allocated(),mem_total());
	printf("%d bytes are free in %d holes; maximum allocatable block is %d bytes.\n",mem_free(),mem_holes(),mem_largest_free());
	printf("average hole size is %f.\n\n",((float)mem_free())/mem_holes());
}

/* use this function to see what happens when your malloc and free
 * implementations are called.  run "mem -try <args>" to call this function.
 * we have given you a simple example to start.
 */
void try_mymem(int argc, char **argv) {
        strategies strat;
	void *a, *b, *c, *d, *e;
	if(argc > 1)
	  strat = strategyfromstring(argv[1]);
	else
	  strat = first;


	/* a simple example.
	   each algorithm should produce a different layout. */
	
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
/*
int main() {
    // strategies strat = Best;
    // void *a, *b, *c, *d, *e;
    // initmem(strat, 500);

    printf("main\n");

    strategies strat = Best;

    initmem(strat, 500);

//    struct memoryList *b = getBestFreeBlock(100);
//
  //  struct memoryList *s = splitBlock(b, 100);
//    printf("Contents of structure %c are %d\n", s, s->size);
    struct memoryList *b =  mymalloc(100);
    printf("Numbers of free holes: %d\n", mem_holes());
    printf("mem_allocated: Bytes allocated %d\n", mem_allocated());
    printf("mem_free: Bytes non-allocated %d\n", mem_free());
    printf("mem_largest_free: Bytes non-allocated %d\n", mem_largest_free());
    printf("mem_small_free: numbers of blocks smaller than 200 non-allocated %d\n", mem_small_free(200));
    if (mem_is_alloc(b))
       printf("mem_is_alloc return 1\n");
    myfree(b);
    if (!mem_is_alloc(b))
        printf("mem_is_alloc return 0\n");
    printf("mem_small_free: numbers of blocks smaller than 200 non-allocated %d\n", mem_small_free(200));
    printf("mem_largest_free: Bytes non-allocated %d\n", mem_largest_free());
    printf("mem_free: Bytes non-allocated %d\n", mem_free());
    printf("mem_allocated: Bytes allocated %d\n", mem_allocated());
    printf("Numbers of free holes: %d\n", mem_holes());
    exit(0);
    void *b1 = getBestFreeBlock(75);

    struct memoryList *s1 = splitBlock(b1, 75);
    printf("Contents of structure %c are %d\n", s1, s1->size);

    void *b2 = getBestFreeBlock(50);

    struct memoryList *s2 = splitBlock(b2, 50);
    printf("Contents of structure %c are %d\n", s2, s2->size);

    print_memory_status();
    printf("main");
    return 0;
}
*/
/*
 * Numbers of free holes: 1
mem_allocated: Bytes allocated 100
mem_free: Bytes non-allocated 400
mem_largest_free: Bytes non-allocated 400
mem_small_free: numbers of blocks smaller than 200 non-allocated 0
mem_is_alloc return 1
myfree: Contents of structure 0 was -> alloc: 1
myfree: Contents of structure 0 is  -> alloc: 0
mem_is_alloc return 0
mem_small_free: numbers of blocks smaller than 200 non-allocated 1
mem_largest_free: Bytes non-allocated 400
mem_free: Bytes non-allocated 500
mem_allocated: Bytes allocated 0
Numbers of free holes: 2
 */