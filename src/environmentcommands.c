/**
* @file environmentcommands.c
* @author Luciano Mantovani
* @date October 2014
* @brief file containing functions that execute the environment commands
*
* this file has all the functions that are called by the function analize() in file environment.c
* they execute each and every possible combination of the command and its arguments
*
* to retrieve the register passed by the argument which holds the register name in string format, we use a set
* of functions taken from the book "C Programming" by Dennis Ritchie and Brian Kernighan.
* This functions are hash(), lookup(), and install(). They allow the creation of a hash table.
*
* @see for more information about lookup: http://zanasi.chem.unisa.it/download/C.pdf 
**/
#include "headers.h"
#include "environmentcommands.h"
#include "elfmanager.h"
#include "disassembler.h"
#include "errors.h"
#include "lookup.h"

struct ptype *env_load(struct ptype *mips)
{
	if(mips->argenv[0] != NULL)
		{
			char *filename = mips->argenv[0];
			mips->elfdata = start_and_load(mips->elfdata, filename);
			mips->report = mips->elfdata->report;
			if(mips->report > 0)
			{
				return mips;
			}
			mips->fl_file_loaded = true;

			printf("\n---NEW FILE LOADED:  %s ---\n",filename);
			int j = 0;
			int i;
		    print_mem(mips->elfdata->memory);
		    for (i=0; i<NB_SECTIONS; i++) {
		        if (is_in_symbols(section_names[i],mips->elfdata->symtab)) {
       				print_segment_raw_content(&mips->elfdata->memory->seg[j]);
		            j++;
		        }
		    }


			mips->report = 0;
			return mips;
		}
	else return mips;
}


/**
* @brief function set. explained in environment documentation
*
* if set mem was entered,
* mem->argenv[1] should have type, 
* mem->argenv[2] should have address , 
* mem->argenv[3] should have value , 
*
* if set reg was entered,
* mem->argenv[1] should have register, 
* mem->argenv[2] should have value , 
*
* @note error code: 410 to 419
*
* @todo read-only permits on certain read-only registers (example: $zero)
**/
struct ptype *env_set(struct ptype *mips)
{
	if(!strcmp(mips->argenv[0],"mem"))
		{
			
			if(mips->n_argenv < 4){mips->report = 410; return mips;} 
			if(mips->n_argenv > 4) {mips->report = 411; return mips;}
			if(!mips->fl_file_loaded){mips->report = 3; return mips;}
			else
			{
				 if(find_illegal_character(mips->argenv[2])){mips->report = 422; return mips;}
				 if(find_illegal_character(mips->argenv[3])){mips->report = 419; return mips;}

				if(!strcmp(mips->argenv[1],"byte"))
				{		
						byte temp;
						vaddr32 addr;
						byte bdata;
						addr = (int)strtol(mips->argenv[2], (char**)NULL,0);

						bdata = (short int)strtol(mips->argenv[3], (char**)NULL,0);
						if(bdata > 0xFF){mips->report = 419; return mips;}

						mips = elfwritebyte(mips, mips->elfdata->memory, bdata, addr); // breaks alone if no writing permits in segment
						return mips;

				}
				else if(!strcmp(mips->argenv[1],"word"))
				{

					word temp;
					vaddr32 addr;
					word wdata;
					addr = (int)strtol(mips->argenv[2], (char**)NULL,0);
					wdata = (int)strtol(mips->argenv[3], (char**)NULL,0);

					if(wdata > 0xFFFFFFFF){mips->report = 419; return mips;}

					if(addr % 4 == 0) //number should be divisable by 4
					{
						mips = elfwriteword(mips,mips->elfdata->memory, wdata, addr); // but the writing is done anyway
						return mips;
					}
					else {mips->report = 415;}
					
				}
 				else {mips->report = 412; return mips;}
			}
		}
	else if(!strcmp(mips->argenv[0], "reg"))
		{
			if(mips->n_argenv < 3){mips->report = 410; return mips;} 
			if(mips->n_argenv > 3) {mips->report = 411; return mips;}


			if(find_illegal_character(mips->argenv[2])){mips->report = 419; return mips;}

			word wdata;
			wdata = (int)strtol(mips->argenv[2], (char**)NULL,0);

			if (wdata < 0 || wdata > 0xFFFFFFFF){mips->report = 419; return mips;}

			int regidx;
			struct nlist *np;

			np = lookup(mips->argenv[1]);
			if(np == NULL){mips->report = 417; return mips;}

			regidx = (int)strtol(np->defn, (char**)NULL,0);
			wdata = (int)strtol(mips->argenv[2], (char**)NULL,0);

			if(regidx == 0) {mips->report = 4171; return mips;}
			
			*(mips->regs[regidx]) = wdata;

			mips->report = 0;
			return mips;
			


		}
	else mips->report = 418;


}

/**
* @brief function disp. explained in environment documentation
*
* if disp mem was entered,
* mem->argenv[1] should have "map" or an address , 
*
* if disp reg was entered,
* mem->argenv[1] should have register or "all", 
*
* @note error code 420 to 429
*
* @todo being able to display a group of specific registers and not only one or all of them
**/
struct ptype *env_disp(struct ptype *mips)
{
	if(!strcmp(mips->argenv[0],"mem"))
	{
	
		if(mips->argenv[1] == NULL){mips->report = 420; return mips;}
		if(mips->n_argenv > 2){mips->report = 411; return mips;}
		if(!mips->fl_file_loaded){mips->report = 3; return mips;}

		if(!strcmp(mips->argenv[1],"map"))
			{
			    int j=0;
			    int i;

			    print_mem(mips->elfdata->memory);
			    for (i=0; i<NB_SECTIONS; i++) {
			        if (is_in_symbols(section_names[i],mips->elfdata->symtab)) {
           				print_segment_raw_content(&mips->elfdata->memory->seg[j]);
			            j++;
			        }
			    }

				mips->report = 0;
				return mips;
			}
		else
		{
			char *temp1, *temp2;
			temp2 = strchr(mips->argenv[1], ':');
			if(!temp2) //if no : are found
			{

				// find_illegal_character(mips->argenv[2]);
				vaddr32 addr = (int)strtol(mips->argenv[1], (char**)NULL,0);
			
				byte bdata;                           //print the byte of the address
				mips = elfreadbyte(mips, mips->elfdata->memory, addr);
				if(mips->report > 0){return mips;}

				printf("0x%x: 0x%x\n",addr, mips->bdata);
				return mips;
			}
			else
			{	
				vaddr32 addr1, addr2;
				byte bdata;

				size_t len = temp2 - mips->argenv[1]; //we retrieve the : out of the string
	            temp1 = malloc(len + 1);
	            memcpy(temp1,mips->argenv[1],len);
	            temp1[len] = '\0';

				addr1 = (int)strtol(temp1, (char**)NULL,0); // and we convert to int

				//then we get the rest of the string, which is the other address
				temp2++;
	            addr2 = (int)strtol(temp2, (char**)NULL,0);

				if(addr1 > addr2) {mips->report = 424; return mips;}

				while(addr1 <= addr2)
				{
					mips = elfreadbyte(mips, mips->elfdata->memory, addr1);
					if(mips->report > 0){return mips;}
					printf("0x%x: 0x%x\n",addr1, mips->bdata);
					addr1++;
				}
				mips->report = 0;
				return mips;
			}
		}

		return mips;
	}
	else if(!strcmp(mips->argenv[0],"reg")) //register display
	{
		if(mips->argenv[1] == NULL){mips->report = 421; return mips;}

		int regidx;
		if(!strcmp(mips->argenv[1], "all")) //display all registers
		{
			for(regidx = 0; regidx < 32; regidx++)
				printf("%s: 0x%x ",regnames[regidx], *(mips->regs[regidx]));
			printf("\n");
			mips->report = 0;
			return mips;
		}

		//display one specific register
		struct nlist *np;
		np = lookup(mips->argenv[1]);
		if(np == NULL){mips->report = 417; return mips;}

		regidx = (int)strtol(np->defn, (char**)NULL,0);
		printf("%s: 0x%x\n",mips->argenv[1], *(mips->regs[regidx]));
		mips->report = 0;
	}
	else {mips->report = 426; return mips;}
	return mips;
}

/**
* @brief function assert. explained in environment documentation
*
* if assert reg was entered,
* mem->argenv[1] should have register, 
* mem->argenv[2] should have value , 
*
* if assert byte or word was entered,
* mem->argenv[1] should have address (divisable by 4 in case of word) , 
* mem->argenv[2] should have value , 
*
* @note error code 430 to 439
**/
struct ptype *env_assert(struct ptype *mips)
{
	if(mips->argenv[0] == NULL){mips->report = 430; return mips;}
	if(!mips->fl_file_loaded){mips->report = 3; return mips;}

	if(!strcmp(mips->argenv[0],"reg"))
	{
		if(mips->argenv[1] == NULL){mips->report = 431; return mips;}
		if(mips->argenv[2] == NULL){mips->report = 432; return mips;}

		int regidx;
		struct nlist *np;
		np = lookup(mips->argenv[1]);
		if(np == NULL){mips->report = 417; return mips;}

		regidx = (int)strtol(np->defn, (char**)NULL,0);
		if(*(mips->regs[regidx]) != (int)strtol(mips->argenv[2], (char**)NULL,0))
		{
			printf("registers differ, value of register %s is: 0x%x\n",mips->argenv[1], *(mips->regs[regidx]));
		}
		mips->report = 0;	
		return mips;

	}
	if(!strcmp(mips->argenv[0],"word"))
	{
		if(mips->argenv[1] == NULL){mips->report = 420; return mips;}
		if(mips->argenv[2] == NULL){mips->report = 432; return mips;}

		int addr = (int)strtol(mips->argenv[1], (char**)NULL,0);

		if(addr % 4 != 0){mips->report = 415; return mips;}

		word wdata = (int)strtol(mips->argenv[2], (char**)NULL,0);
		if(addr < 0 || addr > 0xFFFFFFFF){mips->report = 419; return mips;}

		mips = elfreadword(mips, mips->elfdata->memory, addr);
		if(mips->report > 0){return mips;}

		if(mips->wdata != wdata)
		{
			printf("words differ, word value of address 0x%x is: 0x%x\n",addr, mips->wdata);
		}
		mips->report = 0;	
		return mips;		
	}

	if(!strcmp(mips->argenv[0],"byte"))
	{
		if(mips->argenv[1] == NULL){mips->report = 420; return mips;}
		if(mips->argenv[2] == NULL){mips->report = 432; return mips;}

		int addr = (int)strtol(mips->argenv[1], (char**)NULL,0);
		if(addr < 0 || addr > 0xFF){mips->report = 419; return mips;}

		byte bdata = (int)strtol(mips->argenv[2], (char**)NULL,0);

		mips = elfreadbyte(mips, mips->elfdata->memory, addr);
		if(mips->report > 0){return mips;}

		if(mips->bdata != bdata)
		{
			printf("bytes differ, value of address 0x%x is: 0x%x\n",addr, mips->bdata);
		}
		mips->report = 0;	
		return mips;		
	}

	mips->report = 433;
	return mips;
}



struct ptype *env_disasm(struct ptype *mips)
{
	if(!mips->fl_file_loaded){mips->report = 3; return mips;}
	printf("%d\n", mips->n_argenv);
	if(mips->n_argenv != 1){mips->report = 440; /*usage: disasm address:address or disasm address+address*/ return mips;}

	char *temp, *caddr1, *caddr2;
	vaddr32 addr1, addr2, offset;

	if((temp = strchr(mips->argenv[0], ':')) != NULL)
	{
		caddr1 = strtok(mips->argenv[0], ":");
		caddr2 = strtok(NULL, "\n");
		if(caddr1 == NULL || caddr2 == NULL){mips->report = 441; /*null argument(s)*/ return mips;}
		if(find_illegal_character(caddr1) || find_illegal_character(caddr2)){mips->report = 442; /*bad argument(s)*/ return mips;}

		addr1 = (int)strtol(caddr1, (char**)NULL,0);
		addr2 = (int)strtol(caddr2, (char**)NULL,0);

		if(addr1 > addr2){mips->report = 443; /*addr1 must be smaller than addr2*/ return mips;}

		if(!is_in_segment(get_seg_by_name(mips->elfdata->memory, "text"), addr1, addr2 - addr1)){mips->report = 444; /*disasm must be inside text segment*/ return mips;}

		mips->disasm_output = malloc(50);
		mips->instr_output = malloc(50);
		uint i;
		for(i = addr1; i <= addr2; i++)
		{

			mips = disasm_instr(mips, i, D_PRINT);
			if(mips->report > 0)
				{
					free(mips->disasm_output);
					free(mips->instr_output);
					return mips;
				}

			printf("%x :: %s	%s\n", i, mips->instr_output, mips->disasm_output);
		}

		free(mips->disasm_output);
		free(mips->instr_output);

	}
	else if((temp = strchr(mips->argenv[0], '+')) != NULL)
	{
		caddr1 = strtok(mips->argenv[0], ":");
		caddr2 = strtok(NULL, "\n");
		if(caddr1 == NULL || caddr2 == NULL){mips->report = 441; /*null argument(s)*/ return mips;}
		if(find_illegal_character(caddr1) || find_illegal_character(caddr2)){mips->report = 442; /*bad argument(s)*/ return mips;}

		addr1 = (int)strtol(caddr1, (char**)NULL,0);
		offset = (int)strtol(caddr2, (char**)NULL,0);

		if(addr1 > offset){mips->report = 445; /*addr1 must be smaller than offset*/ return mips;}

		if(!is_in_segment(get_seg_by_name(mips->elfdata->memory, "text"), addr1, offset - addr1)){mips->report = 444; /*disasm must be inside text segment*/ return mips;}

		mips->disasm_output = malloc(50);
		mips->instr_output = malloc(50);

		mips = disasm_instr(mips, addr1, D_PRINT);
		if(mips->report > 0)
			{
				free(mips->disasm_output);
				free(mips->instr_output);
				return mips;
			}
		printf("%x :: %s	%s\n", addr1, mips->instr_output, mips->disasm_output);
		mips = disasm_instr(mips, addr1 + offset, D_PRINT);
		if(mips->report > 0)
			{
				free(mips->disasm_output);
				free(mips->instr_output);
				return mips;
			}
		printf("%x :: %s	%s\n", addr1 + offset, mips->instr_output, mips->disasm_output);
		free(mips->disasm_output);
		free(mips->instr_output);
	}
	else{mips->report = 449;/*invalid argument for disasm*/ return mips;}
}



/*
*@brief this function searches an illegal character in a string that should have a number in decimal, octal or hexadecimal format
*
*@param char* s the string to search
*@return int res 0 if OK, 1 if illegal character found
*
*/
int find_illegal_character(char * s)
{
	int i;
	int res = 0;
	bool hexa = false;

	for (i = 0; i < strlen(s); i++)
		{
			if (i == 1)
			{	
				if(!(s[i] >= 48 && s[i] <= 57) && s[i] != 'x')
					res = 1;
				
				else if(s[i] == 'x')
					hexa = true;
			}
			else
			{
				if(!hexa && !(s[i] >= 48 && s[i] <= 57))
					res = 1;
				else if(hexa && !(s[i] >= 48 && s[i] <= 57) && !(s[i] >= 65 && s[i] <= 70) && !(s[i] >= 97 && s[i] <= 102))
					res = 1;
			}
		}

	return res;		
}
