#include<stdio.h>

void Display (char *str)
{
    int i = 0;
    int ilength = 0;

    printf("The Enter string is : %s\n", str);

    while(*str != '\0')
    {
        ilength++;

        str++;
    }

    printf("Total charater are %d\n", ilength);
}