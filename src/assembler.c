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
 * there's an extra function called splitscript that is used by compile
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

    return mips;
}

/**
*
*@brief this function parses the line entered by user and identifies the tag, the operation and the arguments.
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
    char *line = mips->incoming_line;
    if(strlen(line) == 1){return mips;}

    char *stok;
    char *buffer[7];
    int nbuf = 0;

    while ((stok = strtok(line, " ")) != NULL)
    {   
        buffer[nbuf] = stok;
        nbuf++;
        line = NULL;
    }
    // we have now in buffer, the entire line which shouldn't have more than 7 strings according to MIPS assembler
    //the first element is either a tag, an operation, or a label.
    //if its a label, then it has a ':' character
    
    /// this integer is the index of buffer in which the first argument of the operation is located
    int argidx;
    if(strchr(buffer[0], ':') != NULL)
        {
            mips->label = buffer[0];
            //check to see if the line has ended
            if(nbuf == 1){return mips;}

            //if the first element is a label, then the second one can be a tag or an operation
            if(strchr(buffer[1], '.') != NULL){mips->tag = buffer[1];}
            if(nbuf == 2){return mips;}

            //and the remaining element is the operation
            mips->operation = buffer[2];
            if(nbuf == 3){return mips;}
            argidx = 3;

        }
    else if(strchr(buffer[0], '.') != NULL)
        {
            mips->tag = buffer[0];
            //check to see if the line has ended
            if(nbuf == 1){return mips;}

            //if the first element is a label, then the second one has to be an operation
            mips->operation = buffer[1];
            if(nbuf == 2){return mips;}
            argidx = 2;
        }
    else 
        {
            mips->operation = buffer[0];
            if(nbuf == 1){return mips;}

            argidx = 1;
        }
       //now we add all the arguments
        int i = 0;
        for(argidx; argidx < nbuf - 1; argidx++)
        {
            if((stok = strtok(buffer[argidx], ",")) == NULL)
            {
                //error wtf 
                return mips;
            }

            mips->argline[i] = stok;
            i++;     
        }

        //we load the last argument, which doesn't end in comma
        if(nbuf > 1)
        mips->argline[i] = buffer[argidx];


    return mips;
}

/**
*@brief this function splits the field full_script from a ptype scructure into nlines lines and stores each line in field scriptlines[][] from the same structure
*
* this function is not yet being used by the program due to bugs in parseline
*
*
**/
struct ptype *splitscript(struct ptype *mips)
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
        s = token + 1;

        if(temp != NULL)
        {
            // printf("va a agregar: %s, %zu\n", temp, strlen(temp));
            if(strlen(temp) > 1)
            {
                mips->scriptlines[mips->nlines] = temp;
                mips->nlines++; 
            }
        }

        // printf("scriptlines[%d]: %s\n",mips->nlines - 1,mips->scriptlines[mips->nlines - 1] );
    }

    // printf("\nsalio del while\n");
    // int i;
    // for(i = 0; i < mips->nlines; i++)
    //     printf("scriptlines[%d]: %s\n",i,mips->scriptlines[i] );

    return mips;

    }
}

struct ptype *clearline(struct ptype *mips)
{
    mips->label = NULL;
    mips->tag = NULL;
    mips->operation = NULL;
    mips->argline[0] = NULL;
    mips->argline[1] = NULL;
    mips->argline[2] = NULL;
    mips->argline[3] = NULL;

    return mips;
}

