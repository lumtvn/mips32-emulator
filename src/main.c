/**
 * @file main.c
 * @author Luciano Mantovani
 * @date October 2014
 * @brief file containing the main function. It starts the program and calls the main functions
 * 
 *
 *
 **/
#include "headers.h"

int main(int argc, char *argv[])
{
	struct ptype data;
	struct ptype *pdata = &data;

	if((pdata->filename = argv[1]) != NULL)
		{
			pdata = compile(pdata);				
		}

	
}