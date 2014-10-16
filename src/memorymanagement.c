#include "headers.h"
#include "memorymanagement.h"


/**
* @brief creates a block of memory for a specific tag. Could be .text, .data, etc..
*
*uses the fields size, simpoint, and tag from a structure mmemory to create a new block.
*this block will have a size mem->size, will start from memory position mem->simpoint, and
*will have a mem->tag tag.
*
*@todo exception handling
**/
struct mmemory *createtagblock(struct mmemory *mem)
{
	if((mem->realpointbase = malloc(mem->blocksize)) == NULL)
	{
		printf("asdasd\n");
	}

	return mem;
}
/**
*@brief writes the byte stored in mem->databyte, to a specific block with name mem->tag
*
*
*
**/
struct mmemory *writebyte(struct mmemory *mem)
{
	mem->realpoint = mem->realpointbase + mem->simpoint;
	*(mem->realpoint) = mem->bdata & 0xFF;

	return mem;

}
/**
*@brief writes a halfword in memory, using a big endian format
*
* writes the data in variable mem->hwdata to the simulated direction mem->simbase
*
*
**/
struct mmemory *writehalfword(struct mmemory *mem)
{
	mem->realpoint = mem->realpointbase + mem->simpoint;
	*(mem->realpoint) = (mem->hwdata >> 8) & 0xFF;

	mem->realpoint = mem->realpointbase + mem->simpoint + 1;
	*(mem->realpoint) = mem->hwdata & 0xFF;

	return mem;
}

struct mmemory *writeword(struct mmemory *mem)
{
	mem->realpoint = mem->realpointbase + mem->simpoint;
	*(mem->realpoint) = (mem->wdata >> 24) & 0xFF;

	mem->realpoint = mem->realpointbase + mem->simpoint + 1;
	*(mem->realpoint) = (mem->wdata >> 16) & 0xFF;

	mem->realpoint = mem->realpointbase + mem->simpoint + 2;
	*(mem->realpoint) = (mem->wdata >> 8) & 0xFF;

	mem->realpoint = mem->realpointbase + mem->simpoint + 3;
	*(mem->realpoint) = mem->wdata & 0xFF;

	return mem;

}



struct mmemory *readbyte(struct mmemory *mem)
{
	mem->realpoint = mem->realpointbase + mem->simpoint;
	mem->bdata = *(mem->realpoint);

	return mem;

}

struct mmemory *readhalfword(struct mmemory *mem)
{
	mem->realpoint = mem->realpointbase + mem->simpoint;
	mem->hwdata = (*mem->realpoint << 8) | *(mem->realpoint+1);

	return mem;
}
struct mmemory *readword(struct mmemory *mem)
{
	mem->realpoint = mem->realpointbase + mem->simpoint;
	mem->wdata = (*(mem->realpoint) << 24) | (*(mem->realpoint+1) << 16) | (*(mem->realpoint+2) << 8) | *(mem->realpoint+3);

	return mem;
}


/**
*@brief displays a whole block of memory of a certain tag
*
*
**/
void displaymemory(struct mmemory *mem)
{
	int i = 0;
	while (i < mem->blocksize)
	{
		printf("%x %x\n",i, *(mem->realpointbase));
		mem->realpointbase++;
		i++;
	}
}
