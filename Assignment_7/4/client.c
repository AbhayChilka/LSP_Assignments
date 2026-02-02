#include<stdio.h>
#include<dlfcn.h>
#include<stdlib.h>

int main()
{
    char str[50] = {'\0'};

    printf("Enter string : ");
    scanf("%[^\n]", str);
    void *handle = NULL;

    int (*fp)(char[]);

    int iRet = 0;
    char *err;

    handle = dlopen("./libmystring.so", RTLD_LAZY);

    if(handle == NULL)
    {
        printf("Unable to load the library\n");
        return -1;
    }

    fp = (int(*)(char[]))dlsym(handle, "MyStrlen");

    err = dlerror();
    if(err != NULL)
    {
        printf("dlsym failed: %s\n", err);
        dlclose(handle);
        return -1;
    }

    iRet = fp(str);

    printf("Lenth of enter string is : %d\n",iRet);
    dlclose(handle);

    return 0;
}