#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int strang(char *s);

int main()
{
    int BUFFSIZE = 256;
    char prueba[BUFFSIZE];

    fgets(prueba,BUFFSIZE,stdin);
    strang(prueba);
    
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