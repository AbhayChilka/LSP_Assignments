/**
C program create two shared libraries

library 1 : libperfect.so 
contains function:
    int IsPerfect(int No);

library 2 : libhelper.so
contains helper functions used by IsPerfect():
    int SumOfFactors(int No);(or)
    int IsFactor(int No, int i); (any helper logic)

Requirements
1. libperfect.so must internally call helper function(s) from libhelper.so
2. Client application should call only IsPerfect() from libperfect.so
3. Demonstrate linking chain:
        Client->libperfect.so->libhelper.so

Deliverables
. helper.c, helper.h -> libhelper.so
. perfect.c, perfect.h -> libperfect.so(linked with libhelper)
.client.c 
*/

#include<stdio.h>
#include<dlfcn.h>
#include<stdlib.h>
#include "perfect.h"

int main()
{
    int No = 0;

    void *handle = NULL;

    int (*fp)(int);

    int iRet = 0;
    char *err;

    printf("Enter Number : ");
    scanf("%d", &No);

    handle = dlopen("./libperfect.so", RTLD_LAZY);

    if(handle == NULL)
    {
        printf("Unable to load the library\n");
        return -1;
    }

    printf("Library gets loaded successfully\n");

    fp = (int(*)(int))dlsym(handle, "IsPerfect");

    err = dlerror();
    if(err != NULL)
    {
        printf("dlsym failed: %s\n", err);
        dlclose(handle);
        return -1;
    }

    iRet = fp(No);

    dlclose(handle);

    if(iRet == No)
    {
        printf("%d is perfect number\n", No);
    }
    else
    {
        printf("%d is not perfect number\n", No);
    }
    
    return 0;
}