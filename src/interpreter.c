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
struct ptype *parse(struct ptype *data){

	char *buffer1;
	char *buffer2;

	printf("data->incoming_line: '%s'\n",data->incoming_line);

	buffer1 = strtok(data->incoming_line, "#"); // we temporarely put the incoming line into a buffer1 to get rid of the commentaries
	
	printf("buffer1: '%s'\n", buffer1);
	//and now we parse	
    buffer2 = strtok(buffer1, " ");

    printf("buffer2: '%s'\n",buffer2);

    //at this moment, buffer2 holds either a tag or the comment. 
    if(buffer2[0] == '.')
    	{
    		data->tag = buffer2; //if the first caracter of buffer2 is a dot ".", then its a tag
    		data->operation = strtok(NULL, " "); // and the second string is the operation
    	}
    else 	data->operation = buffer2; //if it's not, then it has to be the operation

   	//the rest of the string remaining in buffer1 are the arguments. so we continue parsing
    int i = 0;
    while ((buffer2 = strtok(NULL, " ")) != NULL && i < 4)
    {
    	data->arg[i] = buffer2;
    	i++;
    }

    //we proceed to clean the commas out of the arguments. It had to be done separatedly from the
    //previous while becouse if not, strtok doesn't work correctly

    i = 0;
     while ((buffer2 = strtok(data->arg[i], ",")) != NULL || i < 4)
    {
    	data->arg[i] = buffer2;
    	i++;
    }


    printf("data->tag: '%s'\n", data->tag);
    printf("data->operation: '%s'\n", data->operation);
    printf("data->arg[0]: '%s'\n", data->arg[0]);
    printf("data->arg[1]: '%s'\n", data->arg[1]);
    printf("data->arg[2]: '%s'\n", data->arg[2]);
    printf("data->arg[3]: '%s'\n", data->arg[3]);

    free(buffer1);
    free(buffer2);



	return data;
}