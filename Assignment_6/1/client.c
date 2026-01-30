#include<stdio.h>
#include<dlfcn.h>
#include<stdlib.h>

int main()
{
    void *handle = NULL;

    int (*fp)(int, int);

    int iRet = 0;

    handle = dlopen("./libserver1.so", RTLD_LAZY);

    if(handle == NULL)
    {
        printf("Unable to load the library\n");
        return -1;
    }

    printf("Library gets loaded successfully\n");

    fp = (int(*)(int , int))dlsym(handle, "Addition");

    if(fp == NULL)
    {
        printf("Unable to get address of function\n");
        dlclose(handle);
        return -1;
    }

    iRet = fp(11,10);

    printf("Addition is %d\n", iRet);

    fp = (int(*)(int , int))dlsym(handle, "Subtraction");

    if(fp == NULL)
    {
        printf("Unable to get address of function\n");
        dlclose(handle);
        return -1;
    }

    iRet = fp(11,10);

    printf("Subtraction is %d\n", iRet);

    dlclose(handle);

    return 0;
}
