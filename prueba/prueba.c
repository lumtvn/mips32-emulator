#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

typedef int bool;
#define true 1
#define false 0


int main()
{
    char *succ1 = "0x00FAFA";
    char *succ2 = "0x012322";
    char *succ3 = "032292";
    char *fail1 = "f78fd78as";
    char *fail2 = "0x0GHTT";
    char *fail3 = "0x0xxx0x";

    printf("succ1: %d\n", find_illegal_character(succ1));
    printf("succ2: %d\n", find_illegal_character(succ2));
    printf("succ3: %d\n", find_illegal_character(succ3));
    printf("fail1: %d\n", find_illegal_character(fail1));
    printf("fail2: %d\n", find_illegal_character(fail2));
    printf("fail3: %d\n", find_illegal_character(fail3));

    return 0;
}


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
					res = -1;
				
				else if(s[i] == 'x')
					hexa = true;
			}
			else
			{
				if(!hexa && !(s[i] >= 48 && s[i] <= 57))
					res = -1;
				else if(hexa && !(s[i] >= 48 && s[i] <= 57) && !(s[i] >= 65 && s[i] <= 70) && !(s[i] >= 97 && s[i] <= 102))
					res = -1;
			}
		}

	return res;		
}