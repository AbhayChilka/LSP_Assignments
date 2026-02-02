#include<stdio.h>
#include<dlfcn.h>
#include<stdlib.h>
#include "perfect.h"
#include "helper.h"

int IsPerfect(int NO)
{
    printf("Inside perfect so");
    if(NO < 0)     // Updator
    {
        NO = -NO; 
    }

    void *handle = NULL;

    int (*fp)(int);

    int iRet = 0;
    char *err;

    handle = dlopen("./libhelper.so", RTLD_LAZY);

    if(handle == NULL)
    {
        printf("Unable to load the library\n");
        return -1;
    }

    printf("Library gets loaded successfully\n");

    dlerror();

    fp = (int(*)(int))dlsym(handle, "SumOfFactors");

    err = dlerror();
    if(err != NULL)
    {
        printf("dlsym failed: %s\n", err);
        dlclose(handle);
        return -1;
    }

    iRet = fp(NO);

    dlclose(handle);

    return iRet;
}