#include<stdio.h>
#include<dlfcn.h>
#include<stdlib.h>

int main()
{
    char str1[50] = {'\0'};

    printf("Enter string 1: ");
    scanf("%[^\n]", str1);

    char str2[50] = {'\0'};

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

    iRet = fp(str1);

    printf("Lenth of enter string 1 is : %d\n",iRet);

    //////////////////////////////////////////////////////

    char*(*cp)(char[], char[]);

    cp = (char*(*)(char[], char[]))dlsym(handle, "MyStrcpy");

    err = dlerror();
    if(err != NULL)
    {
        printf("dlsym failed: %s\n", err);
        dlclose(handle);
        return -1;
    }

    cp(str2, str1);

    printf("Data from str 1 : %s\n", str1);
    printf("Data from str 2 : %s\n", str2);

    dlclose(handle);

    return 0;
}