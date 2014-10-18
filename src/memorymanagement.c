/**
 * @file memorymanagement.c
 * @author Luciano Mantovani
 * @date October 2014
 * @brief file containing functions to write bytes, halfwords and words to a simulated memory
 *
 * this file is used by the environment and the code assembler to read from and write to
 * a simulated memory in the MIPS32 processor. The simulated memory comes from a real portion
 * of RAM memory of the HOST PC. 
 *
 * the set of write and read functions are thougt for a sistem that will store the bytes
 * in memory using "big endian". Naturally, this emulator should run in big endian
 * and little endian processors. That is why each each write and read function has a few
 * code lines that convert the incoming data in to big endian, no matter the format of the
 * incoming data (big or little endian).
 *
 * @todo the block of memory should be created with a tag that identifies it, this is yet to be implemented
 **/

#include "headers.h"
#include "memorymanagement.h"


/**
* @brief creates a block of memory
*
*uses a structure ptype and an integer size to create a new block.
*this block will have a size mem->size and will start from memory position mem->realpointbase.
*
**/
struct ptype *createblock(struct ptype *mem, int size)
{
	mem->realpointbase = malloc(size);
	mem->blocksize = size;

	return mem;
}
/**
*@brief writes the byte stored in mem->bdata to the position inside the block given by simpoint
*
*
*
**/
struct ptype *writebyte(struct ptype *mem, mbyte bdata, int simpoint)
{
	mem->realpoint = mem->realpointbase + simpoint;
	*(mem->realpoint) = bdata & 0xFF;

	return mem;

}
/**
*@brief writes the halfword stored in mem->hwdata to the position inside the block given by simpoint
*
**/
struct ptype *writehalfword(struct ptype *mem, mhalfword hwdata, int simpoint)
{
	mem->realpoint = mem->realpointbase + simpoint;
	*(mem->realpoint) = (hwdata >> 8) & 0xFF;

	mem->realpoint = mem->realpointbase + simpoint + 1;
	*(mem->realpoint) = hwdata & 0xFF;

	return mem;
}

/**
*@brief writes the word stored in wdata to the position inside the block given by simpoint
*
**/
struct ptype *writeword(struct ptype *mem, mword wdata, int simpoint)
{
	mem->realpoint = mem->realpointbase + simpoint;
	*(mem->realpoint) = (wdata >> 24) & 0xFF;

	mem->realpoint = mem->realpointbase + simpoint + 1;
	*(mem->realpoint) = (wdata >> 16) & 0xFF;

	mem->realpoint = mem->realpointbase + simpoint + 2;
	*(mem->realpoint) = (wdata >> 8) & 0xFF;

	mem->realpoint = mem->realpointbase + simpoint + 3;
	*(mem->realpoint) = wdata & 0xFF;

	return mem;

}


/**
*@brief reads the byte stored in simulated address simpoint and stores it in mem->bdata
*
**/
mbyte readbyte(struct ptype *mem, int simpoint)
{
	mbyte bdata;
	mem->realpoint = mem->realpointbase + simpoint;
	bdata = *(mem->realpoint);

	return bdata;

}

/**
*@brief reads the halfword stored in simulated address simpoint and stores it in mem->hwdata
*
**/
mhalfword readhalfword(struct ptype *mem, int simpoint)
{
	mhalfword hwdata;
	mem->realpoint = mem->realpointbase + simpoint;
	hwdata = (*mem->realpoint << 8) | *(mem->realpoint+1);

	return hwdata;
}

/**
*@brief reads the word stored in simulated address simpoint and stores it in mem->wdata
*
**/
mword readword(struct ptype *mem, int simpoint)
{
	mword wdata;
	mem->realpoint = mem->realpointbase + simpoint;
	wdata = (*(mem->realpoint) << 24) | (*(mem->realpoint+1) << 16) | (*(mem->realpoint+2) << 8) | *(mem->realpoint+3);

	return wdata;
}


/**
*@brief displays a whole block of memory of size mem->blocksize, starting at address mem->realpointbase
*
*
**/
void displaymemory(struct ptype *mem)
{
	int i = 0;
	while (i < mem->blocksize)
	{
		printf("%x %x\n",i, *(mem->realpointbase));
		mem->realpointbase++;
		i++;
	}
}
