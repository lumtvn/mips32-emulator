#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

int strang(char *s);

int main()
{
    FILE *fp;
    char *file = "../test/test_elf.o";
    fp = fopen(file, "r");

    if(fp == NULL)
    {
        printf("%s", strerror(errno));
        printf("asdk\n");
    }



    return 0;
}
int strang(char *s)
{
    char *s1;

    if((s1 = strtok(s, " ")) != NULL)
    {
    printf("s1: %s\n string ingresado: %s\n",s1,s);
    }

    return 0;
}