#include "headers.h"
#include "memorymanagement.h"


/**
* @brief creates a block of memory for a specific tag. Could be .text, .data, etc..
*
*
* @todo exception handling
**/
struct *mmemory createtagblock(struct *mmemory mem);
{
	mem->simbase = 0;
	mem->realbase = malloc(mem->size);

	return mem;
}