#include<stdio.h>
#include<stdlib.h>

int Addition(int A, int B);
int Subtraction(int A, int B);
int Multiplication(int A, int B);

int main()
{
    int iRet = 0;
    
    iRet = Addition(11,10);
    printf("Additon is : %d\n", iRet);

    iRet = Subtraction(11,10);
    printf("Subtraction is : %d\n", iRet);

    iRet = Multiplication(11,10);
    printf("Multiplication is : %d\n", iRet);

    return 0;
}

// command -  ar rcs libclient1.a client1.o
//rcs  replace create symbol index
// ar - archive utility 
