#include<stdio.h>
#include<dlfcn.h>
#include<stdlib.h>

int main()
{
    void *handle = NULL;

    int (*fp)(int, int);

    int iRet = 0;
    char *err;

    ///RTLD_NOW
    handle = dlopen("./libServer.so", RTLD_NOW);

    if(handle == NULL)
    {
        printf("Unable to load the library\n");
        return -1;
    }

    printf("Library gets loaded successfully using NOW\n");

    dlerror();
    fp = (int(*)(int , int))dlsym(handle, "Addition");

    err = dlerror();
    if(err != NULL)
    {
        printf("dlsym failed: %s\n", err);
    }

    iRet = fp(11,10);
    printf("Addition is %d\n", iRet);

    dlerror();
    fp = (int(*)(int , int))dlsym(handle, "Multi");

    err = dlerror();
    if(err != NULL)
    {
        printf("dlsym failed: %s\n", err);
        return -1;
    }

    iRet = fp(11,10);
    printf("Subtraction is %d\n", iRet);

    dlclose(handle);

    return 0;
}
