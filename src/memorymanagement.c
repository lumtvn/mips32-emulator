/**
 * @file memorymanagement.c
 * @author Luciano Mantovani
 * @date October 2014
 * @brief file containing functions to write bytes, halfwords and words to a simulated memory
 *
 * this file is used by the environment and the code disassembler to read from and write to
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
#include "lookup.h"

/**
* @brief sets up a segment's parameters
*
* this function does not literally create a segment inside a memory block. Instead, it loads
* the information concerning a created segment into a lookup table, which will be referenced
* when reading from or writing to a segment.
*
* @param name the name of the segment
* @param name the size of the segment
* @param name the permissions of the segment
* @param name the direction of the beggining of the segment
*
*
*
**/
struct ptype *createsegment(struct ptype *mips, char *name, int size, int permissions, int start)
{
	struct nlist *np;

	char *segname = malloc(20);
	if(segname == NULL){mips->report = 0; printf("malloc null\n"); return mips;}
	char *segsize = malloc(20);
	if(segsize == NULL){mips->report = 0; printf("malloc null\n"); return mips;}
	char *segperm = malloc(20);
	if(segperm == NULL){mips->report = 0; printf("malloc null\n"); return mips;}
	char *segstart = malloc(20);
	if(segstart == NULL){mips->report = 0; printf("malloc null\n"); return mips;}
	
	strcpy(segsize, "SEGSIZE_");
	strcat(segsize, name);

	strcpy(segperm, "SEGPERM_");
	strcat(segperm, name);

	strcpy(segstart, "SEGSTART_");
	strcat(segstart, name);

	char *ssize = malloc(10);
	if(ssize == NULL){mips->report = 0; printf("malloc null\n"); return mips;}
	char *spermissions = malloc(10);
	if(spermissions == NULL){mips->report = 0; printf("malloc null\n"); return mips;}
	char *sstart = malloc(10);
	if(sstart == NULL){mips->report = 0; printf("malloc null\n"); return mips;}

	sprintf(ssize, "%i", size);
	sprintf(spermissions, "%i", permissions);
	sprintf(sstart, "%x", start);

	// printf("installing %s in block %s\n",ssize, segsize);
	np = install(segsize, ssize);
	if(np == NULL){mips->report = 0; printf("no install\n"); return mips;}
	np = install(segperm, spermissions);
	if(np == NULL){mips->report = 0; printf("no install\n"); return mips;}
	np = install(segstart, sstart);
	if(np == NULL){mips->report = 0; printf("no install\n"); return mips;}

	free(segstart);
	free(segperm);
	free(segname);
	free(sstart);
	free(ssize);
	free(spermissions);

	return mips;
}


/**
* @brief creates a block of memory
*
*uses a structure ptype and an integer size to create a new block.
*this block will have a size mips->size and will start from memory position mips->memrealpointbase.
*
**/
struct ptype *creatememory(struct ptype *mips, int size)
{
	mips->memrealpointbase = malloc(size);
	if(mips->memrealpointbase == NULL){mips->report = 0; printf("malloc null\n"); return mips;}
	mips->memsize = size;

	return mips;
}


struct ptype *destroymemory(struct ptype *mips)
{
	if(mips->memrealpointbase != NULL)
	free(mips->memrealpointbase);
	else
	{
		printf("null pointer??????\n");
	}

	return mips;
}
/**
*@brief writes the byte stored in mips->bdata to the position inside the block given by simpoint
*
*
*
**/
struct ptype *writebyte(struct ptype *mips, mbyte bdata, int simpoint)
{
	mips->memrealpoint = mips->memrealpointbase + simpoint;
	*(mips->memrealpoint) = bdata;

	return mips;

}
/**
*@brief writes the halfword stored in mips->hwdata to the position inside the block given by simpoint
*
**/
struct ptype *writehalfword(struct ptype *mips, mhalfword hwdata, int simpoint)
{
	mips->memrealpoint = mips->memrealpointbase + simpoint;
	*(mips->memrealpoint) = (hwdata >> 8) & 0xFF;

	mips->memrealpoint = mips->memrealpointbase + simpoint + 1;
	*(mips->memrealpoint) = hwdata;

	return mips;
}

/**
*@brief writes the word stored in wdata to the position inside the block given by simpoint
*
**/
struct ptype *writeword(struct ptype *mips, mword wdata, int simpoint)
{
	mips->memrealpoint = mips->memrealpointbase + simpoint;
	*(mips->memrealpoint) = (wdata >> 24) & 0xFF;

	mips->memrealpoint = mips->memrealpointbase + simpoint + 1;
	*(mips->memrealpoint) = (wdata >> 16) & 0xFF;

	mips->memrealpoint = mips->memrealpointbase + simpoint + 2;
	*(mips->memrealpoint) = (wdata >> 8) & 0xFF;

	mips->memrealpoint = mips->memrealpointbase + simpoint + 3;
	*(mips->memrealpoint) = wdata;

	return mips;

}


/**
*@brief reads the byte stored in simulated address simpoint and stores it in mips->bdata
*
**/
mbyte readbyte(struct ptype *mips, int simpoint)
{
	mbyte bdata;
	mips->memrealpoint = mips->memrealpointbase + simpoint;
	bdata = *(mips->memrealpoint);

	return bdata;

}

/**
*@brief reads the halfword stored in simulated address simpoint and stores it in mips->hwdata
*
**/
mhalfword readhalfword(struct ptype *mips, int simpoint)
{
	mhalfword hwdata;
	mips->memrealpoint = mips->memrealpointbase + simpoint;
	hwdata = (*mips->memrealpoint << 8) | *(mips->memrealpoint+1);

	return hwdata;
}

/**
*@brief reads the word stored in simulated address simpoint and stores it in mips->wdata
*
**/
mword readword(struct ptype *mips, int simpoint)
{
	mword wdata;
	mips->memrealpoint = mips->memrealpointbase + simpoint;
	wdata = (*(mips->memrealpoint) << 24) | (*(mips->memrealpoint+1) << 16) | (*(mips->memrealpoint+2) << 8) | *(mips->memrealpoint+3);

	return wdata;
}


/**
*@brief displays a whole block of memory of size mips->memsize, starting at address mips->memrealpointbase
*
*
**/
struct ptype *displaymemory(struct ptype *mips)
{
	int i = 0;
	mips->memrealpoint = mips->memrealpointbase;
	while (i < mips->memsize)
	{
		printf("%x %x\n",i, *(mips->memrealpoint));
		mips->memrealpoint++;
		i++;
	}

	return mips;
}
