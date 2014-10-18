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
#include "assembler.h"
#include "environment.h"
#include "memorymanagement.h"

int main(int argc, char *argv[])
{
	struct ptype mips;
	struct ptype *pmips = &mips;

	int size = 100;
	pmips = createblock(pmips, size);

	if((pmips->filename = argv[1]) != NULL)
		{
			pmips = compile(pmips);				
		}

	while(1)
	{
	runenv(pmips);
	}
	
}