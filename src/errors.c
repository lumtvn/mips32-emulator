/**
* @file errors.c
* @author Luciano Mantovani
* @date October 2014
* @brief file containgin all the error and warning reports, delivered by a switch case
*
* all the errors and warnings have a code. This codes varies according to the file and function from which this
* error comes from. Each code is given by the file EREADME.txt
*
*
**/
#include <stdio.h>

void report(int r)
{
	switch(r)
	{

		case 101:	fprintf(stderr, "ERROR %d: the file does not exist or the path is incorrect\n", r); break;
		case 201:	fprintf(stderr, "ERROR %d: invalid argument. vaild arguments: mem, reg\n", r); break;
		case 410: 	fprintf(stderr, "ERROR %d: missing argument <type>\n", r); break;
		case 411: 	fprintf(stderr, "ERROR %d: missing argument <address>\n", r); break;
		case 412: 	fprintf(stderr, "ERROR %d: missing argument <value>\n", r); break;
		case 413: 	fprintf(stderr, "WARNING %d: rewriting data in address\n", r); break;
		case 420: 	fprintf(stderr, "ERROR %d: missing argument <address>+\n", r); break;
		default: fprintf(stderr, "no output for this report number\n"); break;
	}
}