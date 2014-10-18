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

	
	// strcpy(pmips->regnames[0],"$zero");
	// strcpy(pmips->regnames[1],"$at");
	// strcpy(pmips->regnames[2],"$v0");
	// strcpy(pmips->regnames[3],"$v1");
	// strcpy(pmips->regnames[4],"$a0");
	// strcpy(pmips->regnames[5],"$a1");
	// strcpy(pmips->regnames[6],"$a2");
	// strcpy(pmips->regnames[7],"$a3");
	// strcpy(pmips->regnames[8],"$t0");
	// strcpy(pmips->regnames[9],"$t1");
	// strcpy(pmips->regnames[10],"$t2");
	// strcpy(pmips->regnames[11],"$t3");
	// strcpy(pmips->regnames[12],"$t4");
	// strcpy(pmips->regnames[13],"$t5");
	// strcpy(pmips->regnames[14],"$t6");
	// strcpy(pmips->regnames[15],"$t7");
	// strcpy(pmips->regnames[16],"$s0");
	// strcpy(pmips->regnames[17],"$s1");
	// strcpy(pmips->regnames[18],"$s2");
	// strcpy(pmips->regnames[19],"$s3");
	// strcpy(pmips->regnames[20],"$s4");
	// strcpy(pmips->regnames[21],"$s5");
	// strcpy(pmips->regnames[22],"$s6");
	// strcpy(pmips->regnames[23],"$s7");
	// strcpy(pmips->regnames[24],"$t8");
	// strcpy(pmips->regnames[25],"$t9");
	// strcpy(pmips->regnames[26],"$k0");
	// strcpy(pmips->regnames[27],"$k1");
	// strcpy(pmips->regnames[28],"$gp");
	// strcpy(pmips->regnames[29],"$sp");
	// strcpy(pmips->regnames[30],"$fp");
	// strcpy(pmips->regnames[31],"$ra");


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