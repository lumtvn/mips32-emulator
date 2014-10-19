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
#include "lookup.h"

void hashregisters();
struct ptype *initregisters(struct ptype *pmips);

int main(int argc, char *argv[])
{

	

	struct ptype mips;
	struct ptype *pmips = &mips;

	hashregisters();
	pmips = initregisters(pmips);
	int size = 20;
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

struct ptype *initregisters(struct ptype *pmips)
{
	int i;
	for(i = 0; i < 32; i++)
	{
		pmips->regs[i] = malloc( sizeof(int) );
		*(pmips->regs[i]) = 0;
	}
	return pmips;
}

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