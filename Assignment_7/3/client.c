#include<stdio.h>
#include<dlfcn.h>
#include<stdlib.h>

int main()
{
    char str[50] = {'\0'};

    printf("Enter string : ");
    scanf("%[^\n]", str);
    void *handle = NULL;

    void (*fp)(char[]);

    int iRet = 0;
    char *err;

    handle = dlopen("./libdisplay.so", RTLD_LAZY);

    if(handle == NULL)
    {
        printf("Unable to load the library\n");
        return -1;
    }

    fp = (void(*)(char[]))dlsym(handle, "Display");

    err = dlerror();
    if(err != NULL)
    {
        printf("dlsym failed: %s\n", err);
        dlclose(handle);
        return -1;
    }

    fp(str);

    dlclose(handle);

    return 0;
}