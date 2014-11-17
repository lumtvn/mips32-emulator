/**
 * @file main.c
 * @author Luciano Mantovani
 * @date October 2014
 * @brief file containing the main function. It starts the program and calls the principal functions
 * 
 *
 *
 **/
#include "headers.h"
#include "disassembler.h"
#include "environment.h"
#include "memorymanagement.h"
#include "lookup.h"
// #include "../elfapi/include/elf/elf.h"
// #include "../elfapi/include/elf/format.h"

void hashregisters();
struct ptype *initregisters(struct ptype *mips);
struct ptype *allocatemips(struct ptype *mips);
void destroymips(struct ptype *mips);



/**
* @brief the main function
*
* -initializes the general mips structure which holds all the simulator general information.
*
* -initializes the registers and creates the hash table of the registers using the function lookup.
* this function was taken from the book "C Programming" by Dennis Ritchie and Brian Kernighan.
* The complete set of functions are hash(), lookup(), and install(). They allow the creation of hash tables.
*
* -creates a single memory block in which the emulator will work, reading and wirting memory slots.
* the functionality to create many memory blocks and asingn tags to them is not yet implemented
*
* -if the program was called with an argument, it will try to open it as a file and compile its content
*
* -after all of this is done, it will run the environment in an endless loop, until "exit" is entered
**/
int main(int argc, char *argv[])
{
	struct ptype *mips;
	mips = allocatemips(mips);
	if(mips->report > 0){report(mips->report); return 0;}

	hashregisters();
	mips = initregisters(mips);


	int size = 20;
	mips = creatememory(mips, size);

	if((mips->filename = argv[1]) != NULL)
		{
			// mips = compile(mips);				
		}

	while(1)
	{
	runenv(mips);
	}

	destroymips(mips);

	return 0;
	
}

/**
*@brief initializes the registers, giving them a portion of memory and setting to 0 their content
**/
struct ptype *initregisters(struct ptype *mips)
{
	int i;
	for(i = 0; i < 32; i++)
	{
		*(mips->regs[i]) = 0;
	}
	return mips;
}

/**
*@brief sets the hash table that holds the names of the registers, and its identifier (number)
**/
void hashregisters()
{
	install("$zero", "0");
	install("$at", "1");
	install("$v0", "2");
	install("$v1", "3");
	install("$a0", "4");
	install("$a1", "5");
	install("$a2", "6");
	install("$a3", "7");
	install("$t0", "8");
	install("$t1", "9");
	install("$t2", "10");
	install("$t3", "11");
	install("$t4", "12");
	install("$t5", "13");
	install("$t6", "14");
	install("$t7", "15");
	install("$s0", "16");
	install("$s1", "17");
	install("$s2", "18");
	install("$s3", "19");
	install("$s4", "20");
	install("$s5", "21");
	install("$s6", "22");
	install("$s7", "23");
	install("$t8", "24");
	install("$t9", "25");
	install("$k0", "26");
	install("$k1", "27");
	install("$gp", "28");
	install("$sp", "29");
	install("$fp", "30");
	install("$ra", "31");
}

struct ptype *allocatemips(struct ptype *mips)
{
	//general structure allocation
	mips = malloc(sizeof(mips));

	//segment allocations
	if(mips == NULL){mips->report = 1; return mips;}
	mips->segname = malloc(20);
	if(mips->segname == NULL){mips->report = 1; return mips;}
	mips->segsize = malloc(20);
	if(mips->segsize == NULL){mips->report = 1; return mips;}
	mips->segperm = malloc(20);
	if(mips->segperm == NULL){mips->report = 1; return mips;}
	mips->segstart = malloc(20);
	if(mips->segstart == NULL){mips->report = 1; return mips;}


	int i;
	for(i = 0; i < 32; i++)
	{
		mips->regs[i] = malloc(sizeof(int));
		if(mips->regs[i] == NULL){mips->report = 1; return mips;}
	}

	return mips;
}


void destroymips(struct ptype *mips)
{
	free(mips->segname);
	free(mips->segsize);
	free(mips->segperm);
	free(mips->segstart);

	free(mips->memrealpointbase);

	free(mips);
}
