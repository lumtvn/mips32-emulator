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
                *(mips->full_script + i) = key;
                comm = false;
                i++;
            }
            else if(key == '#')
            {
                comm = true;
            }
            else if(!comm)
            {
                *(mips->full_script + i) = key;
                i++;
            }
        }
    fclose (file);
    *(mips->full_script + i) = '\0';

   // printf("%s", mips->full_script);

    mips->report = 0;
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

    while ((stok = strtok(line, " ")) != NULL && nbuf < 7)
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
    char *stok, *s;
    mips->nlines = 0;

    s = mips->full_script;

    if (s != NULL) {

    stok = strtok(s, "\n");
    while (stok != NULL)
    {   
        if(strlen(stok) > 1)
        {
            mips->scriptlines[mips->nlines] = stok;
            mips->nlines++;
        }
        stok = strtok(NULL, "\n");
    }

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

