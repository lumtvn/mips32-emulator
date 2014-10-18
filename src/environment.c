#include "headers.h"
#include "environment.h"
#include "memorymanagement.h"
#include "environmentcommands.h"
#include "errors.h"


/**
*@brief this function runs the environment program and allows the user to enter commands
*
* 
**/
void runenv(struct ptype *mips)
{

			 mips->entry = malloc(MAXSIZE);


			printf("emul-mips>"); // prints out the prompt
			
			char *result = fgets(mips->entry,MAXSIZE,stdin);  
			if (result == NULL)
			{
				printf("\n");    
				exit(0);
			}
			mips = parseentry(mips);													

			mips = analize(mips); 

			if(mips->report != 0)
				report(mips->report);
				// fprintf(stderr, "bue..\n");

			restart(mips);	
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



struct ptype *parseentry(struct ptype *mips)
{

	char *buffer;
    char *temp1;
    char *temp2 = NULL;
    mips->n_argenv = 1; //initialized to 1 by default, it updates later if there are any arguments

	 // printf("mips->entry: '%s'\n",mips->entry);

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
	
	// printf("command: %s\n", mips->command);

	// for(i = 0; i < mips->n_argenv; i++)
	// 	printf("arguments :%s\n", mips->argenv[i]);


	return mips;
}


struct ptype *analize(struct ptype *mips)
{

	if(!strcmp(mips->command,"exit"))
    {
    	printf("exiting mips emulator...\n");
    	exit(0);   
    }
	else if(!strcmp(mips->command,"load"))	mips = env_load(mips);

	else if(!strcmp(mips->command,"disp"))	mips = env_disp(mips);

	else if(!strcmp(mips->command,"disasm"))	printf("disasm was entered...\n");

	else if(!strcmp(mips->command,"set"))	mips = env_set(mips);

	else if(!strcmp(mips->command,"assert"))	printf("assert was entered...\n");

	else if(!strcmp(mips->command,"debug"))	printf("debug was entered...\n");

	else if(!strcmp(mips->command,"resume"))	printf("resume was entered...\n");

	else if(!strcmp(mips->command,"run"))	printf("run was entered...\n");

	else if(!strcmp(mips->command,"step"))	printf("step was entered...\n");

	else if(!strcmp(mips->command,"break"))	printf("break was entered...\n");

	else printf("command '%s' not found\n",mips->command);

	return mips;

}

/**this function simply discards unwanted characters in a string*/
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