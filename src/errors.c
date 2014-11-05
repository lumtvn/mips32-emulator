/**
* @file errors.c
* @author Luciano Mantovani
* @date October 2014
* @brief file containing all the error and warning reports, delivered by a switch case
*
* all the errors and warnings have a code. This codes varies according to the file and function from which this
* error comes from. Each code is given by the file EREADME.txt
*
*
**/
#include <stdio.h>
#include "headers.h"

void report(int r)
{
	switch(r)
	{

		case 100:	fprintf(stderr, "ERROR %d: the file does not exist or the path is incorrect\n", r); break;
		case 201:	fprintf(stderr, "ERROR %d: invalid argument. vaild arguments: mem, reg\n", r); break;
		case 410: 	fprintf(stderr, "ERROR %d: too few arguments for function\n", r); break;
		case 411: 	fprintf(stderr, "ERROR %d: too many arguments for function\n", r); break;
		case 412: 	fprintf(stderr, "ERROR %d: unknown type, expected 'byte' or 'word'\n", r); break;
		case 413: 	fprintf(stderr, "WARNING %d: rewriting data in address\n", r); break;
		case 414: 	fprintf(stderr, "ERROR %d: address not in memory block\n", r); break;
		case 415: 	fprintf(stderr, "ERROR %d: address is not aligned\n", r); break;
		case 416: 	fprintf(stderr, "ERROR %d: argument missing: register\n", r); break;
		case 417: 	fprintf(stderr, "ERROR %d: bad register name (lookup)\n", r); break;
		case 4171: 	fprintf(stderr, "WARNING %d:register $zero can't be overwritten, was not overwritten\n", r); break;
		case 418: 	fprintf(stderr, "ERROR %d: no valid argument for 'set'\n", r); break;
		case 419: 	fprintf(stderr, "ERROR %d: argument <value> out of bounds\n", r); break;
		case 420: 	fprintf(stderr, "ERROR %d: argument missing: address\n", r); break;
		case 421: 	fprintf(stderr, "ERROR %d: no register(s) entered\n", r); break;
		case 422: 	fprintf(stderr, "ERROR %d: argument <address> out of bounds\n", r); break;
		case 423: 	fprintf(stderr, "ERROR %d: second address not valid\n", r); break;
		case 424: 	fprintf(stderr, "ERROR %d: second address can't be smaller than the first one\n", r); break;
		case 425: 	fprintf(stderr, "ERROR %d: word reaches outside of memory block\n", r); break;
		case 430: 	fprintf(stderr, "ERROR %d: assert argument null (reg, word, byte)\n", r); break;
		case 431: 	fprintf(stderr, "ERROR %d: argument missing or invalid: register\n", r); break;
		case 432: 	fprintf(stderr, "ERROR %d: argument missing or invalid: value\n", r); break;
		case 1000: 	fprintf(stderr, "COMPILATION ERROR %d: symbol table load failed\n", r); break;
		// case 1001: 	fprintf(stderr, "COMPILATION ERROR %d: operation not found: %s\n", r, mips->operation); break;
		default: fprintf(stderr, "no output for this report number: %d\n", r); break;
	}
}