/**
 * @file reader.c
 * @author Luciano Mantovani
 * @date October 2014
 * @brief file containing functions used by main to read a new elf script
 *
 * This file has functions called by the main program when it has to read a new elf script. 
 * The reading of a new file, includes also the removal of the commentary.
 *
 * the only parameter taken in this and in every function in all source files is a pointer
 * to a struct mips type. It makes it easier to handle information between functions.
 *
 **/
#include "headers.h"
#include "reader.h"

/**
*
*@brief this function reads an incoming script, and removes the commentary from it
*@param *mips A pointer to a ptype structure, created by the main program.
*@return it returns the same structure, but with mips->full_script modified(it now has the script, with the commentaries striped)
*@todo the size of the string that holds the entire file should be modified when once the commentaries are removed
*@errorcode 100 -> 109
*/
struct ptype *readscript(struct ptype *mips)
{   
    FILE *file;
    bool comm;
    char key;
    int i;

    if((file = fopen ( mips->filename, "r" )) == NULL)
    {
        mips->report = 100;
        return mips;
    }

    fseek(file, 0, SEEK_END); // seek to end of file
    mips->filesize = ftell(file); // get current file pointer
    fseek(file, 0, SEEK_SET); // seek back to beginning of file

    if((mips->full_script = malloc(mips->filesize + 1)) == NULL)
    {
        //error print, no memory available for malloc in script assignment
        return mips;
    }

    comm = false;
    i = 0;
    while ((key = fgetc (file)) != EOF ) /* read a character */
        {
            if(key == '\n')
            {
                if(!comm)
                *(mips->full_script + i) = key;
                comm = false;
            }
            else if(key == '#')
            {
                comm = true;
            }
            else if(!comm)
            {
                *(mips->full_script + i) = key;
            }
            i++;
        }
    fclose (file);
    *(mips->full_script + i) = '\0';

    mips->report = 0;
    return mips;
}

/**
*@brief this function simply removes the commentary from a char * using the string function "strchr"
*
*
*
*
*@todo: this doesn't contemplate yet the case in which there's a # character surrounded by commas ""
*/
char *removecommentary(char *s)
{   
    char *temp1;
    char *temp2;

    temp1 = strchr(s,'#');

    if(temp1) // if temp1 isn't null, then there's a commentary in this line
        {
            size_t len = temp1 - s;
            temp2 = malloc(len + 1);
            memcpy(temp2,s,len);
            temp2[len] = '\0';
            //now temp2 has the line without the commentary
            return temp2;
        }
   
    else    return s; //if strchr returns null, there's nothing to do   
}
    