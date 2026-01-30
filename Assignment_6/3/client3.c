
#include<stdio.h>
#include<dlfcn.h>
#include<stdlib.h>

int main()
{   
    int Choice = 0;
    int A = 0;
    int B = 0;

    void *handle = NULL;

    int (*fp)(int, int);
    float (*fpp)(int, int);

    int iRet = 0;
    float fRet = 0;
    char *err;

    handle = dlopen("./libserver3.so", RTLD_LAZY);

    if(handle == NULL)
    {
        printf("Unable to load the library\n");
        return -1;
    }

    printf("Library gets loaded successfully\n");

    printf("Enter No1 : ");
    scanf("%d", &A);

    printf("Enter No2 : ");
    scanf("%d", &B);

    printf("Enter choice which operation want to execute\n");
    printf(" press 1 for Addition\n press 2 for Subtraction\n press 3 for Multiplication\n press 4 for Division\n ->");
    scanf("%d", &Choice);

    switch (Choice)
    {
        case 1:
            dlerror();
            fp = (int(*)(int , int))dlsym(handle, "Addition");

            err = dlerror();
            if(err != NULL)
            {
                printf("dlsym failed: %s\n", err);
                dlclose(handle);
                return -1;
            }

            iRet = fp(A,B);

            printf("Addition is %d\n", iRet);
            
            break;
        
        case 2 :
            dlerror();
            fp = (int(*)(int , int))dlsym(handle, "Subtraction");

            err = dlerror();
            if(err != NULL)
            {
                printf("dlsym failed: %s\n", err);
                dlclose(handle);
                return -1;
            }

            iRet = fp(A,B);

            printf("Subtraction is %d\n", iRet);
            
            break;

        case 3 :
           dlerror();
           fp = (int(*)(int , int))dlsym(handle, "Multiplication");

            err = dlerror();
            if(err != NULL)
            {
                printf("dlsym failed: %s\n", err);
                dlclose(handle);
                return -1;
            }

            iRet = fp(A,B);

            printf("Multiplication is %d\n", iRet);

            break;

        case 4 :
            dlerror();
            fpp = (float(*)(int , int))dlsym(handle, "Division");

            err = dlerror();
            if(err != NULL)
            {
                printf("dlsym failed: %s\n", err);
                dlclose(handle);
                return -1;
            }

            fRet = fpp(A,B);

            printf("Division is %f\n", fRet);

            break;

        default:
            printf("Invalid choice\n");
            break;
    }

    dlclose(handle);

    return 0;
}
