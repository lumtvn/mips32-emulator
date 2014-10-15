/**
 * @file assembler.c
 * @author Luciano Mantovani
 * @date October 2014
 * @brief file containing functions meant to assemble the code from an elf script
 *
 * This file has functions called by the main program when it has to assemble an elf script.
 * 
 *
 * the only parameter taken in this and in every function in all source files is a pointer
 * to a struct data type. It makes it easier to handle information between functions.
 *
 **/
#include "headers.h"
#include "reader.h"
#include "assembler.h"
#include "errors.h"

/**
*
* @brief this function calls the other functions in this file and in others, to compile an elf script
* 
* @param *data A pointer to a ptype structure, created by the main program.
* @return it returns the pointer to the same structure, but modified
* @note ptype type variables that modifies: full_script 
* @todo for now, this only reads a script and prints it in the screen, many things to do yet
*/
struct ptype *compile(struct ptype *data)
{	

	data = readscript(data);
    if(data->report != 0)
        {
            fprintf(stderr, "%s\n", errs[data->report]);
            return data;
        }

	//printf("\n\n%s\n\n",data->full_script);

    return data;
}

/**
*
*@brief this function parses the line entered by user and identifies the tag, the operation, the arguments, and gets rid of the commentaries
*
* @param *data A pointer to a ptype structure, created by the main program.
* @return it returns the pointer to the same structure, but it modifies data->operation and data->argline[]
*
* @note this functions is meant to parse lines from an elf script, not the commands from the environment. there's another file with functions for that
*/
struct ptype *parseline(struct ptype *data)
{

	char *buffer;
    char *temp1;
    char *temp2 = NULL;

    buffer = strtok(data->incoming_line, " ");

    //at this moment, buffer holds either a tag, a label or the operation. 
    //if it holds a label, then buffer has a double colon at the end. we locate this using strchr()

    temp1 = strchr(buffer, ':');
    if(temp1) //this is here in case strchr returns null, in which case there is no label
        {
            size_t len = temp1 - buffer;
            temp2 = malloc(len + 1);
            memcpy(temp2,buffer,len);
            temp2[len] = '\0';
            //now temp2 has the label
            data->label = temp2;
            buffer = strtok(NULL, " "); // and then we load the second string of buffer to buffer
        }

        // now we search for the tag
    if(buffer[0] == '.')
        {
            data->tag = buffer; //if the first character of buffer is a dot, then its a tag
            data->operation = strtok(NULL, " "); //and then follows the command.
        }
    else    data->operation = buffer; //if it's not a tag or a label, then it has to be the operation

    //the rest of the string remaining in buffer are the arguments. so we continue parsing
    int i = 0;
    while ((buffer = strtok(NULL, " ")) != NULL && i < 4)
    {
        data->argline[i] = buffer;
        i++;
    }

    //we proceed to clean the commas out of the arguments. It had to be done separatedly from the
    //previous while becouse if not, strtok doesn't work correctly

    i = 0;
     while ((buffer = strtok(data->argline[i], ",")) != NULL && i < 4)
    {
    	data->argline[i] = buffer;
    	 i++;
    }

	return data;
}