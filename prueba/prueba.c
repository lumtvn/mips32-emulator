#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int strang(char *s);

int main()
{
    unsigned int a = 0x83AABBCC;
    unsigned int b;
    b = a & 0xFC000000;
    b = b >> 26;
    char c;
    c = b;

    printf("%x\n",b);

    char d = 1;
    d = d << 2;
    printf("%x\n",d);


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