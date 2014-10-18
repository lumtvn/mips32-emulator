#include "headers.h"
#include "environmentcommands.h"
#include "memorymanagement.h"
#include "assembler.h"
#include "errors.h"

struct ptype *env_load(struct ptype *mips)
{
	if(mips->argenv[0] != NULL)
		{
			mips->filename = mips->argenv[0];
			mips = compile(mips);
			return mips;
		}
	else return mips;
}
/**
* @brief function set. explained in environment documentation
*
* if set mem was entered,
* mem->argenv[1] should have <type>
* mem->argenv[2] should have <address>
* mem->argenv[3] should have <value>
*
* if set reg was entered,
* mem->argenv[1] should have <register>
* mem->argenv[2] should have <value>
* 
* @errorcode 410 -> 420
**/
struct ptype *env_set(struct ptype *mips)
{
	if(!strcmp(mips->argenv[0],"mem"))
		{
			
			if(mips->argenv[1] == NULL)
				mips->report = 410;
			else if(mips->argenv[2] == NULL)
				mips->report = 411;
			else if(mips->argenv[3] == NULL)
				mips->report = 412;
			else
			{

				if(!strcmp(mips->argenv[1],"byte") && atoi(mips->argenv[2]) < mips->blocksize)
				{
					mbyte temp;
					mword addr;
					mbyte bdata;
					addr = atoi(mips->argenv[2]);
					bdata = atoi(mips->argenv[3]);
					printf("mips->argenv[3]: %d\n", atoi(mips->argenv[3]));

					temp = readbyte(mips,addr); // check to see if we are overwriting
					if(temp != 0) {mips->report = 413;} //if we are, we send a warning
					else {mips->report = 0;} 

					mips = writebyte(mips, addr, bdata); // but the writing is done anyway

					return mips;
				}



			}

			mips->report = 0;
		}
	else if(!strcmp(mips->argenv[0], "reg"))
		{
			printf("set reg was entered\n");
			mips->report = 0;
		}
	else mips->report = 2;


}

struct ptype *env_disp(struct ptype *mips)
{
	if(!strcmp(mips->argenv[0],"mem"))
	{
		if(mips->argenv[1] == NULL)
			{
				mips->report = 420;
				return mips;
			}
		else
		{
			if(!strcmp(mips->argenv[1],"map"))
				{
					displaymemory(mips);
					mips->report = 0;
					return mips;
				}
				return mips;
		}
		return mips;
	}
	return mips;
}