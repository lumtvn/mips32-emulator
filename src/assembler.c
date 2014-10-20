/**
 * @file assembler.c
 * @author Luciano Mantovani
 * @date October 2014
 * @brief file containing functions meant to assemble the code from an elf script
 *
 * This file has functions called by the main program when it has to assemble an elf script.
 * 
 * for now, it only has two main functions: compile and parseline. The idea is to parse line per line
 * and store the assembler code in memory, but this is not yet implemented. For now, the only thing
 * this assembler does is read a text from an .elf file, remove the commentary and store it in a 
 * string, which is a field of the general structure ptype.
 *
 * there's an extra function called splitstr that is used by compile
 **/
#include "headers.h"
#include "reader.h"
#include "assembler.h"
#include "errors.h"
#include "environment.h"

/**
*
* @brief this function calls the other functions in this file and in others, to compile an elf script
* for now, this function only reads a file. It's all it can do for the moment. The objetive for the
* first increment was to be able to include a "debug" command in a script and that way check the status
* of the processor after the last instruction befor "debug" was excecuted. But there were some bugs found
* at the last moment with function parseline that made this not possible.
*
* @param *mips A pointer to a ptype structure, created by the main program.
* @return it returns the pointer to the same structure, but modified
* @note ptype type variables that modifies: full_script 
* @todo "debug" and "restart"
*/
struct ptype *compile(struct ptype *mips)
{	

	mips = readscript(mips);
    if(mips->report != 0)
        {
            report(mips->report);
            return mips;
        }

    // mips = splitstr(mips);

    //     int i;

    //     for(i = 0; i < mips->nlines; i++)
    //     printf("scriptline %d: '%s'\n",i, mips->scriptlines[i]);

    //     for(i = 0; i < mips->nlines; i++)
    //     {
    //         printf("scriptlines[%d]: %s\n", i,mips->scriptlines[i]);
    //         mips->incoming_line = mips->scriptlines[i];
    //         mips = parseline(mips);
    //         printf("parsing: %s\n", mips->incoming_line);

    //         if(mips->operation != NULL)
    //         if(!strcmp(mips->operation, "debug"))
    //             {   
    //                 printf("stopped compiling at line: %s\n",mips->incoming_line);
    //                 while(!strcmp(mips->command, "resume"))
    //                 runenv(mips);
    //             }
    //     }   

    //     printf("return??\n");
    // return mips;
}

/**
*
*@brief this function parses the line entered by user and identifies the tag, the operation, the arguments, and gets rid of the commentaries
*
* @param *mips A pointer to a ptype structure, created by the main program.
* @return it returns the pointer to the same structure, but it modifies mips->operation and mips->argline[]
*
* @note this functions is meant to parse lines from an elf script, not the commands from the environment. there's another file with functions for that
*
* @todo fix bugs. It's not working as it should.
*/
struct ptype *parseline(struct ptype *mips)
{

	char *buffer;
    char *temp1;
    char *temp2 = NULL;

    if(mips->incoming_line == NULL){return mips;} //no line

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
            //and then follows the command.
            mips->operation = strtok(NULL, " ")) == NULL //if there's no operation, we just return
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

/**
*@brief this function splits the field full_script from a ptype scructure into nlines lines and stores each line in field scriptlines[][] from the same structure
*
* this function is not yet being used by the program due to bugs in parseline
*
*
**/
struct ptype *splitstr(struct ptype *mips)
{
    char *token, *tofree, *s;
    mips->nlines = 0;

    s = mips->full_script;

    if (s != NULL) {

    while ((token = strchr(s, '\n')) != NULL)
    {   
        char *temp;
        size_t len = token - s;
        temp = malloc(len + 1);
        memcpy (temp,s,len);
        temp[len] = '\0';
        s += token - s + 1;

        if(temp != NULL)
        {
            mips->scriptlines[mips->nlines] = temp;
            mips->nlines++;
        }
    }

    return mips;

    }
}