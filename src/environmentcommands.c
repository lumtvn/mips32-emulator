#include "headers.h"
#include "environmentcommands.h"
#include "memorymanagement.h"
#include "assembler.h"
#include "errors.h"
#include "lookup.h"

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

				if(!strcmp(mips->argenv[1],"byte"))
				{
					if(atoi(mips->argenv[2]) < mips->blocksize)
					{
						mbyte temp;
						mword addr;
						mbyte bdata;
						addr = atoi(mips->argenv[2]);
						struct nlist np;
						bdata = atoi(mips->argenv[3]);

						temp = readbyte(mips,addr); // check to see if we are overwriting
						if(temp != 0) {mips->report = 413;} //if we are, we send a warning
						else {mips->report = 0;} 

						mips = writebyte(mips, bdata, addr); // but the writing is done anyway

						return mips;
					}
					else mips->report = 414;
						 return mips;
				}
				else if(!strcmp(mips->argenv[1],"word"))
				{
					if(atoi(mips->argenv[2]) < mips->blocksize)
					{

						mword temp;
						mword addr;
						mword wdata;
						addr = atoi(mips->argenv[2]);
						struct nlist np;
						wdata = atoi(mips->argenv[3]);
						if(addr % 4 == 0)
						{
							temp = readword(mips,addr); // check to see if we are overwriting
							if(temp != 0) {mips->report = 413;} //if we are, we send a warning
							else {mips->report = 0;} 

							mips = writeword(mips, wdata, addr); // but the writing is done anyway

							return mips;
						}
						else {mips->report = 415;}
					}
					else mips->report = 414;
						 return mips;	
				}
 


			}

			mips->report = 0;
		}
	else if(!strcmp(mips->argenv[0], "reg"))
		{
			if(mips->argenv[1] == NULL){mips->report = 416; return mips;}
			else if(mips->argenv[2] == NULL)
				{mips->report = 412; return mips;}
			else if (atoi(mips->argenv[2]) < 0 || atoi(mips->argenv[2]) > 0x4000000000000)
				{mips->report = 419; return mips;}

			else
			{
				int regidx;
				mword wdata;
				struct nlist *np;

				np = lookup(mips->argenv[1]);
				if(np == NULL){mips->report = 417; return mips;}

				regidx = atoi(np->defn);
				wdata = atoi(mips->argenv[2]);

				*(mips->regs[regidx]) = wdata;

				mips->report = 0;
				return mips;
			}


		}
	else mips->report = 418;


}
struct ptype *env_disp(struct ptype *mips)
{
	if(!strcmp(mips->argenv[0],"mem"))
	{
	
		if(mips->argenv[1] == NULL){mips->report = 420; return mips;}

		if(!strcmp(mips->argenv[1],"map"))
			{
				mips = displaymemory(mips);
				mips->report = 0;
				return mips;
			}
		else
		{
			char *temp1, *temp2;
			temp2 = strchr(mips->argenv[1], ':');
			if(!temp2) //if no : are found
			{
				mword addr = atoi(mips->argenv[1]);
				if(addr < 0 || addr > mips->blocksize){mips->report = 422; return mips;}
			
				mbyte bdata;                           //print the byte of the address
				bdata = readbyte(mips,addr);
				printf("%x: %x\n",addr, bdata);
				return mips;
			}
			else
			{	
				mword addr1, addr2;
				mbyte bdata;

				size_t len = temp2 - mips->argenv[1]; //we retrieve the : out of the string
	            temp1 = malloc(len + 1);
	            memcpy(temp1,mips->argenv[1],len);
	            temp1[len] = '\0';

				addr1 = atoi(temp1); // and we convert to int

				//then we get the rest of the string, which is the other address
				temp2++;
	            addr2 = atoi(temp2);

				if(addr1 > addr2) {mips->report = 424; return mips;}

				while(addr1 <= addr2)
				{
					bdata = readbyte(mips, addr1);
					printf("%x: %x\n",addr1, bdata);
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
				printf("%s: %d ",regnames[regidx], *(mips->regs[regidx]));
			printf("\n");
			mips->report = 0;
			return mips;
		}

		//display one specific register
		struct nlist *np;
		np = lookup(mips->argenv[1]);
		if(np == NULL){mips->report = 417; return mips;}

		regidx = atoi(np->defn);
		printf("%s: %d\n",mips->argenv[1], *(mips->regs[regidx]));
		mips->report = 0;
	}
	return mips;
}


struct ptype *env_assert(struct ptype *mips)
{
	if(mips->argenv[0] == NULL){mips->report = 430; return mips;}
	if(!strcmp(mips->argenv[0],"reg"))
	{
		if(mips->argenv[1] == NULL){mips->report = 431; return mips;}
		if(mips->argenv[2] == NULL){mips->report = 432; return mips;}

		int regidx;
		struct nlist *np;
		np = lookup(mips->argenv[1]);
		if(np == NULL){mips->report = 417; return mips;}

		regidx = atoi(np->defn);
		if(*(mips->regs[regidx]) != atoi(mips->argenv[2]))
		{
			printf("registers differ, value of register %s is: %x\n",mips->argenv[1], *(mips->regs[regidx]));
		}
		mips->report = 0;	
		return mips;

	}
	if(!strcmp(mips->argenv[0],"word"))
	{
		if(mips->argenv[1] == NULL){mips->report = 420; return mips;}
		if(mips->argenv[2] == NULL){mips->report = 432; return mips;}

		int addr = atoi(mips->argenv[1]);
		if(addr < 0 || addr > mips->blocksize){mips->report = 422; return mips;}
		if(addr % 4 != 0){mips->report = 415; return mips;}

		mword wdata = atoi(mips->argenv[2]);
		if(addr < 0 || addr > 0x4000000000000){mips->report = 419; return mips;}

		mword rwdata;
		rwdata = readword(mips,addr);

		if(rwdata != wdata)
		{
			printf("words differ, word value of address %x is: %x\n",addr, rwdata);
		}
		mips->report = 0;	
		return mips;		
	}

	if(!strcmp(mips->argenv[0],"byte"))
	{
		if(mips->argenv[1] == NULL){mips->report = 420; return mips;}
		if(mips->argenv[2] == NULL){mips->report = 432; return mips;}

		int addr = atoi(mips->argenv[1]);
		if(addr < 0 || addr > mips->blocksize){mips->report = 422; return mips;}

		mbyte bdata = atoi(mips->argenv[2]);
		if(addr < 0 || addr > 0x4000000000000){mips->report = 4210; return mips;}

		mbyte rbdata;
		rbdata = readbyte(mips,addr);

		if(rbdata != bdata)
		{
			printf("bytes differ, value of address %x is: %x\n",addr, rbdata);
		}
		mips->report = 0;	
		return mips;		
	}

	mips->report = 433;
	return mips;
}



// enum {INIT , DECIMAL ZERO , DEBUT HEXA , HEXA , DECIMAL , OCTAL};
// int strtoint()
// {
// 	int c;
// 	int S=INIT;
// 	FILE *pf;
// 	if ((pf=fopen("nombres.txt" ,"rt"))==NULL) 
// 	{
// 		perror("erreurd'ouverturefichier");return1;
// 	}
// 	while(EOF!=(c=fgetc(pf)))
// 	{
// 		switch(S)
// 		{
// 			case INIT:
// 					i=0;
// 					if(isdigit(c))
// 					{
// 						S=(c=='0')?DECIMALZERO:DECIMAL;
// 					}
// 					else if(isspace(c)) S=INIT;
// 					else if(c==EOF) return0;

// 					break;

// 			case DECIMALZERO:/*reperageduprefixedel'hexa*/
					
// 					if(c=='x'||c=='X')S=HEXA;
					
// 					else if(isdigit(c) && c < '8')S=OCTAL;/*c'estunoctal*/

// 					else if(c==EOF||isspace(c))
// 							{
// 								S=INIT;
// 							}
// 					break;

// 			case DEBUTHEXA:
// 					if(isxdigit(c))S=HEXA;

// 					break;

// 			case HEXA:
// 					if(isxdigit(c))S=HEXA;

// 					else if(c==EOF||isspace(c))
// 							{
// 								S=INIT;
// 							}
// 					break;

// 			case DECIMAL:/*tantquec'estunchiffre*/
// 					if(isdigit(c))S=DECIMAL;
// 					else if(c==EOF||isspace(c))
// 						{
// 							S=INIT;
// 						}
// 					break;

// 			case OCTAL:/*tantquec'estunchiffre*/
// 					if(isdigit(c)&&c<'8')S=OCTAL;

// 					elseif(c==EOF||isspace(c))
// 						{
// 							S=INIT;
// 						}
// 			break;
// 			}
// 	}
// 	return 0;
// }