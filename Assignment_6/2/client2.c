/*
    Write a C program to demonstrate runtime dynamic linking in Linux

    -> Load a shared library using dlopen()
    -> Fetch function address using dlsym()
    -> Handle error using dlerror()
    -> Release the library using dlclose()

    Explain the role of each function used in program
*/

#include<stdio.h>
#include<dlfcn.h>
#include<stdlib.h>

int main()
{
    void *handle = NULL;

    int (*fp)(int, int);

    int iRet = 0;
    char *err;

    handle = dlopen("./libserver2.so", RTLD_LAZY);

    if(handle == NULL)
    {
        printf("Unable to load the library\n");
        return -1;
    }

    printf("Library gets loaded successfully\n");

    dlerror();
    fp = (int(*)(int , int))dlsym(handle, "Addition");

    err = dlerror();
    if(err != NULL)
    {
        printf("dlsym failed: %s\n", err);
        dlclose(handle);
        return -1;
    }

    iRet = fp(11,10);
    printf("Addition is %d\n", iRet);

    dlerror();
    fp = (int(*)(int , int))dlsym(handle, "Multi");

    err = dlerror();
    if(err != NULL)
    {
        printf("dlsym failed: %s\n", err);
        dlclose(handle);
        return -1;
    }

    iRet = fp(11,10);
    printf("Subtraction is %d\n", iRet);

    dlclose(handle);

    return 0;
}

/*
    dlopen() - 
       The function dlopen() loads the dynamic shared object (shared library) 
       file named by the null-terminated string path and returns
       an opaque "handle" for the loaded object.

       On success, dlopen() return a non-NULL handle for the loaded object.  
       On error (file could not be found, was not
       readable, had the wrong format, or caused errors during loading),
       these functions return NULL.

    dlsym() -
       The function dlsym() takes a "handle" of a dynamic loaded shared
       object returned by dlopen(3) along with a null-terminated symbol
       name, and returns the address where that symbol is loaded into memory. 

       On success, these functions return the address associated with
       symbol.  On failure, they return NULL; the error can be diagnosed
       using dlerror(3).

    dlerror() -
       The dlerror() function returns a human-readable, null-terminated
       string describing the most recent error that occurred from a call
       to one of the functions in the dlopen API since the last call to dlerror(). 
       The returned string does not include a trailing newline.
       
       dlerror() returns NULL if no errors have occurred since
       initialization or since it was last called.

    dlclose() - 
       The dlclose() function shall inform the system that the symbol
       table handle specified by handle is no longer needed by the
       application.

       If the referenced symbol table handle was successfully closed,
       dlclose() shall return 0. If handle does not refer to an open
       symbol table handle or if the symbol table handle could not be
       closed, dlclose() shall return a non-zero value. 
*/
