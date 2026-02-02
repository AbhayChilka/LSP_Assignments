#include<stdio.h>
#include<dlfcn.h>
#include<stdlib.h>

int main()
{
    void *handle = NULL;

    int (*fp)(int, int);

    int iRet = 0;
    char *err;

    handle = dlopen("./libaddition.so", RTLD_LAZY);

    if(handle == NULL)
    {
        printf("Unable to load the library\n");
        return -1;
    }

    fp = (int(*)(int, int))dlsym(handle, "addition");

    err = dlerror();
    if(err != NULL)
    {
        printf("dlsym failed: %s\n", err);
        dlclose(handle);
        return -1;
    }

    iRet = fp(11,10);

    printf("%d\n", iRet);

    dlclose(handle);

    handle = dlopen("./libsubtraction.so", RTLD_LAZY);

    if(handle == NULL)
    {
        printf("Unable to load the library\n");
        return -1;
    }

    fp = (int(*)(int, int))dlsym(handle, "subtraction");

    err = dlerror();
    if(err != NULL)
    {
        printf("dlsym failed: %s\n", err);
        dlclose(handle);
        return -1;
    }

    iRet = fp(11,10);

    printf("%d\n", iRet);

    dlclose(handle);

    return 0;
}