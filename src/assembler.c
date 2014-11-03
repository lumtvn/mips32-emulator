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
#include "lookup.h"

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
    mips = splitscript(mips);

    if(mips->report != 0)
        {
            report(mips->report);
            return mips;
        }

    return mips;
}

struct ptype *firstpass(struct ptype *mips)
{
    int i;
    for(i = 0; i < mips->nlines; i++)
    {
        strcpy(mips->incoming_line, mips->scriptlines[i]);
        if(mips->incoming_line != NULL)
            mips = parseline(mips);

        if(mips->label != NULL)
        {   
            char *s;
            s = malloc(sizeof(int));
            if(s != NULL)
            {
                sprintf(s,"%d",i);
                install(mips->label, s);
                free(s);
            }
        }
        mips = clearline(mips);
    }
}