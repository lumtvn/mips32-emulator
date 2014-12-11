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

		case 1:	fprintf(stderr, "ERROR %d: unable to allocate memory\n", r); break;
		case 2:	fprintf(stderr, "ERROR %d: unable to install in lookup table\n", r); break;
		case 3:	fprintf(stderr, "ERROR %d: operation not permitted until a file is loaded\n", r); break;
		case 100:	fprintf(stderr, "ERROR %d: the file does not exist or the path is incorrect\n", r); break;
		case 101:	fprintf(stderr, "ERROR %d: file entered isn't ELF\n", r); break;
		case 201:	fprintf(stderr, "ERROR %d: invalid argument. vaild arguments: mem, reg\n", r); break;
		case 401:	fprintf(stderr, "ERROR %d: error starting and loading memory with file\n", r); break;
		case 402:	fprintf(stderr, "ERROR %d: starting address missing\n", r); break;
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
		case 426: 	fprintf(stderr, "ERROR %d: invalid argument for 'disp'\n", r); break;
		case 430: 	fprintf(stderr, "ERROR %d: assert argument null (reg, word, byte)\n", r); break;
		case 431: 	fprintf(stderr, "ERROR %d: argument missing or invalid: register\n", r); break;
		case 440: 	fprintf(stderr, "ERROR %d: usage: disasm address:address or disasm address+offset\n", r); break;
		case 441: 	fprintf(stderr, "ERROR %d: null argument(s)\n", r); break;
		case 442: 	fprintf(stderr, "ERROR %d: bad argument(s)\n", r); break;
		case 443: 	fprintf(stderr, "ERROR %d: addr1 must be smaller than addr2\n", r); break;
		case 444: 	fprintf(stderr, "ERROR %d: disasm must be inside text segment\n", r); break;
		case 445: 	fprintf(stderr, "ERROR %d: addr1 must be smaller than offset\n", r); break;
		case 446: 	fprintf(stderr, "ERROR %d: no more memory available\n", r); break;
		case 447: 	fprintf(stderr, "ERROR %d: all addresses must be aligned\n", r); break;
		case 449: 	fprintf(stderr, "ERROR %d: invalid argument for disasm\n", r); break;
		case 450: 	fprintf(stderr, "ERROR %d: usage: break add addresses, break del addressess/all, break list\n", r); break;
		case 451: 	fprintf(stderr, "ERROR %d: not enough arguments. address missing\n", r); break;
		case 452: 	fprintf(stderr, "ERROR %d: illegal character\n", r); break;
		case 453: 	fprintf(stderr, "ERROR %d: can't add breakpoints to area other than text\n", r); break;
		case 454: 	fprintf(stderr, "ERROR %d: all addresess must be aligned\n", r); break;
		case 432: 	fprintf(stderr, "ERROR %d: argument missing or invalid: value\n", r); break;
		case 501: 	fprintf(stderr, "ERROR %d: address not assigned to any segment or overrides end of segment\n", r); break;
		case 502: 	fprintf(stderr, "ERROR %d: seg->content is null\n", r); break;
		case 503: 	fprintf(stderr, "ERROR %d: writing not permitted in this segment. operation canceled\n", r); break;
		case 601:  	fprintf(stderr, "ERROR %d: no file loaded\n", r); break;
		case 602:  	fprintf(stderr, "ERROR %d: reading section out of bounds\n", r); break;
		case 603:  	fprintf(stderr, "ERROR %d: can't dissassemble in section out of text\n", r); break;
		case 604:  	fprintf(stderr, "ERROR %d: couldn't find operation\n", r); break;
		case 610:  	fprintf(stderr, "ERROR %d: operation not implemented or not existant\n", r); break;

		default: fprintf(stderr, "no output for this report number: %d\n", r); break;
	}
}

void op_report(int r)
{
	switch(r)
	{
		case 1:	fprintf(stderr, "ADD ERROR %d: overflow. invalid operation\n", r); break;
		case 10: fprintf(stderr, "COMPILATION ERROR %d, DIV: division by 0\n", r); break;
		case 20: fprintf(stderr, "COMPILATION ERROR %d, JALR: unaligned jump address\n", r); break;
		case 21: fprintf(stderr, "COMPILATION ERROR %d, JR: unaligned jump address\n", r); break;
		case 30: fprintf(stderr, "COMPILATION ERROR %d, LW: address with null data\n", r); break;
		case 31: fprintf(stderr, "COMPILATION ERROR %d, LW: no segment associated in memory location\n", r); break;
		case 40: fprintf(stderr, "COMPILATION ERROR %d, LBU: address with null data\n", r); break;
		case 41: fprintf(stderr, "COMPILATION ERROR %d, LBU: no segment associated in memory location\n", r); break;
		case 50: fprintf(stderr, "COMPILATION ERROR %d, lw: address not aligned\n", r); break;
		case 51: fprintf(stderr, "COMPILATION ERROR %d, lw: address with null data\n", r); break;
		case 52: fprintf(stderr, "COMPILATION ERROR %d, lw: no segment associated in memory location\n", r); break;
		case 60: fprintf(stderr, "COMPILATION ERROR %d: SB: content is null\n\n", r); break;
		case 61: fprintf(stderr, "COMPILATION ERROR %d: SB: no segment associated in memory location\n", r); break;
		case 62: fprintf(stderr, "COMPILATION ERROR %d: SB: writing not permitted in this segment. operation canceled\n", r); break;
		case 70: fprintf(stderr, "COMPILATION ERROR %d: SW: content is null\n\n", r); break;
		case 71: fprintf(stderr, "COMPILATION ERROR %d: SW: no segment associated in memory location\n", r); break;
		case 72: fprintf(stderr, "COMPILATION ERROR %d: SW: writing not permitted in this segment. operation canceled\n", r); break;
		case 74: fprintf(stderr, "COMPILATION ERROR %d: SW: address not aligned\n", r); break;

		default: fprintf(stderr, "no output for this operation report number: %d\n", r); break;
	}
}