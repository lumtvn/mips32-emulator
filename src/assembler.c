/**
 * @file assembler.c
 * @author Luciano Mantovani
 * @date October 2014
 * @brief file containing functions meant to assemble the code from an elf script
 *
 * This file has functions called by the main program when it has to assemble an elf script.
 * 
 * for now, it only has two functions: compile and parseline. The idea is to parse line per line
 * and store the assembler code in memory, but this is not yet implementer. For now, the only thing
 * this assembler does is read a text from an .elf file, remove the commentary and store it in a 
 * string, which is a field of the general structure ptype
 *
 **/
#include "headers.h"
#include "reader.h"
#include "assembler.h"
#include "errors.h"
#include "environment.h"

/**
*
* @brief this function calls the other functions in this file and in others, to compile an elf script
* 
* @param *mips A pointer to a ptype structure, created by the main program.
* @return it returns the pointer to the same structure, but modified
* @note ptype type variables that modifies: full_script 
* @todo for now, this only reads a script and prints it in the screen, many things to do yet
*/
struct ptype *compile(struct ptype *mips)
{	
    char *line, *temp1, *temp2, *buffer;
    mips->operation = NULL; // i do this because if not the comparison a few lines below gives seg fault

	mips = readscript(mips);
    if(mips->report != 0)
        {
            report(mips->report);
            return mips;
        }

    buffer = mips->full_script;
    do
    {   
        temp1 = strchr(buffer, '\n');
        if(temp1) //this is here in case strchr returns null, in which case there is no label
        {
            size_t len = temp1 - buffer;
            temp2 = malloc(len + 1);
            memcpy(temp2,buffer,len);
            temp2[len] = '\0';
            line = temp2;
            buffer += len;
        }
        printf("%s\n", line);
        mips->incoming_line = line;
        mips = parseline(mips);
        printf("seguro hasta aca anda joya\n");

        if(mips->operation != NULL)
        {printf("no es null.. wtf??\n");
        if(!strcmp(mips->operation, "debug"))
        {   
            printf("stopped compiling at line: %s\n",line);
            while(!strcmp(mips->command, "resume"))
            runenv(mips);
        }
        }


    }while (temp1 != NULL);

    return mips;
}

/**
*
*@brief this function parses the line entered by user and identifies the tag, the operation, the arguments, and gets rid of the commentaries
*
* @param *mips A pointer to a ptype structure, created by the main program.
* @return it returns the pointer to the same structure, but it modifies mips->operation and mips->argline[]
*
* @note this functions is meant to parse lines from an elf script, not the commands from the environment. there's another file with functions for that
*/
struct ptype *parseline(struct ptype *mips)
{

	char *buffer;
    char *temp1;
    char *temp2 = NULL;

    buffer = strtok(mips->incoming_line, " ");

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
            mips->label = temp2;
            buffer = strtok(NULL, " "); // and then we load the second string of buffer to buffer
        }

        // now we search for the tag
    if(buffer[0] == '.')
        {
            mips->tag = buffer; //if the first character of buffer is a dot, then its a tag
            mips->operation = strtok(NULL, " "); //and then follows the command.
        }
    else    mips->operation = buffer; //if it's not a tag or a label, then it has to be the operation

    //the rest of the string remaining in buffer are the arguments. so we continue parsing
    int i = 0;
    while ((buffer = strtok(NULL, " ")) != NULL && i < 4)
    {
        mips->argline[i] = buffer;
        i++;
    }

    //we proceed to clean the commas out of the arguments. It had to be done separatedly from the
    //previous while becouse if not, strtok doesn't work correctly

    i = 0;
     while ((buffer = strtok(mips->argline[i], ",")) != NULL && i < 4)
    {
    	mips->argline[i] = buffer;
    	 i++;
    }

	return mips;
}