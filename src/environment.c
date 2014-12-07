/**
 * @file environment.c
 * @author Luciano Mantovani
 * @date October 2014
 * @brief file containing functions to run the environment for the user
 *
 * this file has functions that react to the lines entered by the user. The commands from the
 * file environmentcommands.c are called by functions from this file.
 **/
#include "headers.h"
#include "environment.h"
#include "environmentcommands.h"
#include "errors.h"


/**
*@brief this function runs the environment program and allows the user to enter commands
*
* after obtaining a line from stdin, it parses it and analizes the command. The function
* analize() also executes it, and if there's no report (mips->report = 0) the program leaves.
*F
*@note this function is thought to be called within an endless loop
**/
int runenv(struct ptype *mips)
{

	printf("emul-mips>"); // prints out the prompt
	
	char *result = fgets(mips->entry,MAXSIZE,stdin);  
	if (result == NULL)
	{
		printf("\n");    
		exit(0);
	}

	if (strlen(mips->entry) > 1)
	{
		mips = parseentry(mips);													
		mips = analize(mips); 

		if(mips->report != 0)
			report(mips->report);
		mips->report = 0;

		restart(mips);
	}

	return 0;
}

/**
*@brief this function sets to null the values in command and in argenv array
*
* it just to reset and prepare the variables for the next command
**/
void restart(struct ptype *mips)
{		
	mips->command = NULL;
	int i;
	for (i = 0; i<mips->n_argenv;i++)
		mips->argenv[i] = NULL;
}


/**
*@brief this function parses an entry in the environment
*
* it parses the entire line entered and stores the command in the field char *command from the struct 
* ptype, and stores all the arguments in the field char *argenv[] from the structure ptype
*
**/
struct ptype *parseentry(struct ptype *mips)
{

	char *buffer;
    char *temp1;
    char *temp2 = NULL;
    mips->n_argenv = 1; //initialized to 1 by default, it updates later if there are any arguments

	//and now we parse	
    mips->command = strtok(mips->entry, " ");
    strip(mips->command);

    //the rest of the string remaining in buffer are the arguments. so we continue parsing
    int i = 0;
    while ((buffer = strtok(NULL, " ")) != NULL)
    {	
        mips->argenv[i] = buffer;
        i++;
    }
    mips->n_argenv = i;

	for(i = 0; i < mips->n_argenv; i++)
	strip(mips->argenv[i]);


	return mips;
}

/**
*@brief this function is a distributer, it calls a function from file environmentcommands.c according to the command entered in the entry
*
* 
* the only command that doesn't call any function is exit
**/
struct ptype *analize(struct ptype *mips)
{

	if(!strcmp(mips->command,"exit"))
    {
    	printf("exiting mips emulator...\n");
    	mips->fl_exit = true;
    	mips->report = 0;
    	return mips;
    }
	else if(!strcmp(mips->command,"load")){ mips = env_load(mips); return mips;}

	else if(!strcmp(mips->command,"disp"))	{	mips = env_disp(mips); return mips;}

	else if(!strcmp(mips->command,"disasm")){	printf("disasm was entered...\n"); return mips;}

	else if(!strcmp(mips->command,"set"))	{	mips = env_set(mips); return mips;}

	else if(!strcmp(mips->command,"assert")){	mips = env_assert(mips); return mips;}

	else if(!strcmp(mips->command,"debug"))	{	printf("debug was entered...\n"); return mips;}

	else if(!strcmp(mips->command,"resume")){	printf("resume was entered...\n"); return mips;}

	else if(!strcmp(mips->command,"run"))	{	printf("run was entered...\n"); return mips;}

	else if(!strcmp(mips->command,"step"))	{	printf("step was entered...\n"); return mips;}

	else if(!strcmp(mips->command,"break"))	{	printf("break was entered...\n"); return mips;}

	else printf("command '%s' not found\n",mips->command);

	return mips;

}

/**
*@brief this function simply discards unwanted characters in a string
*
*@param char *s the string to be stripped
*@return void there's no need to return a value since we are working with pointers
*/
void strip(char *s) {
    char *p2 = s;
    while(*s != '\0') {
    	if(*s != '\t' && *s != '\n') {
    		*p2++ = *s++;
    	} else {
    		++s;
    	}
    }
    *p2 = '\0';
}
