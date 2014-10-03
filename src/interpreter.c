/**
 * @file interpreter.c
 * @author Luciano Mantovani
 * @date December 2014
 * @brief file containing functions used by main to parse and interpretate the line entered by user
 *
 * this file blablablablalba
 * 
 * 
 */
#include "headers.h"
#include "interpreter.h"


/**
*
*@brief this function parses the line entered by user and identifies the tag, the operation, the arguments, and gets rid of the commentaries
*
*
*
*/
struct ptype *parseline(struct ptype *data)
{

	char *buffer;
    char *temp1;
    char *temp2 = NULL;

	 // printf("data->incoming_line: '%s'\n",data->incoming_line);

	//and now we parse	
    buffer = strtok(data->incoming_line, " ");

    // printf("buffer: '%s'\n",buffer);

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
            data->tag = buffer; //if the first or second character of buffer is a dot, then its a tag
            data->operation = strtok(NULL, " "); //and then follows the command.
        }
    else    data->operation = buffer; //if it's not a tag or a label, then it has to be the operation

    //the rest of the string remaining in buffer are the arguments. so we continue parsing
    int i = 0;
    while ((buffer = strtok(NULL, " ")) != NULL && i < 4)
    {
        data->arg[i] = buffer;
        i++;
    }

    //we proceed to clean the commas out of the arguments. It had to be done separatedly from the
    //previous while becouse if not, strtok doesn't work correctly

    i = 0;
     while ((buffer = strtok(data->arg[i], ",")) != NULL && i < 4)
    {
    	data->arg[i] = buffer;
    	 i++;
    }


   // free(temp2);



	return data;
}

/**
*
*@brief this function reads an incoming script, and removes the commentary from it
*
*/
struct ptype *readscript(struct ptype *data)
{

    static const char filename[] = "./test/testscript.elf";

    FILE *file = fopen ( filename, "r" );

    size_t filesize;
    fseek(file, 0, SEEK_END); // seek to end of file
    filesize = ftell(file); // get current file pointer
    fseek(file, 0, SEEK_SET); // seek back to beginning of file

    data->full_script = malloc(filesize);

    if ( file != NULL )
        {
            char *line = malloc(MAXSIZE);

            while ( fgets ( line, MAXSIZE, file ) != NULL ) /* read a line */
                {
                    line = removecommentary(line);
                    strcat(data->full_script,line);
                }
            fclose ( file );
        }
    else
        {
            perror ( filename ); /* why didn't the file open? */
        }
    return data;
}
/**
*
*@brief this function interpretates each line of the script entered
*
*/
struct ptype *parsescript(struct ptype *data)
{

    data->incoming_line = strtok(data->full_script, "\n");
        do{

            printf("entra al while\n");
            printf("%s\n",data->incoming_line);

            parseline(data);
            printstatus(data);

        } while((data->incoming_line = strtok(NULL, "\n")) != NULL);

        printf("me sali del while y incoming_line es '%s'\n", data->incoming_line);

    return data;
}


void printstatus(struct ptype *data)
{
            printf("\ndata->label: '%s'\n", data->label);
            printf("data->tag: '%s'\n", data->tag);
            printf("data->operation: '%s'\n", data->operation);
            printf("data->arg[0]: '%s'\n", data->arg[0]);
            printf("data->arg[1]: '%s'\n", data->arg[1]);
            printf("data->arg[2]: '%s'\n", data->arg[2]);
            printf("data->arg[3]: '%s'\n\n", data->arg[3]);
}

/**
*@brief this function simply removes the commentary from a char * using the string function "strchr"
*
*
*
*
* TODO: no esta contemplado el caso en el que haya un caracter # encerrado en comillas
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
    