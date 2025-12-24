/*
    * 2.5 Find Largest File in Directory *
    > Accept directory name
    > Find and print > largest file name and its size in byte
    > Consideronly regular file(ingnore directories)
*/

#include<stdio.h>   // Standard I/O functions like printf()
#include<fcntl.h>   // File control options: open(), O_RDONLY, O_WRONLY
#include<errno.h>   // For errno variable and error codes
#include<unistd.h>  // Provides POSIX system calls: read(), write(), close()
#include<string.h> // String handling functions like strlen(), strcpy(), strcmp(), memset()
#include<sys/stat.h> // Provides definitions for file metadata (struct stat) and functions like stat(), lstat(), fstat()
#include<dirent.h>   // Directory handling functions and structures: opendir(), readdir(), closedir(), struct dirent
#include<sys/types.h>  // Defines system data types used by system calls such as pid_t, size_t, off_t, ino_t

/*
    Function Name : LargeFile
    Description   : Scans a directory and finds the largest regular file
    Input         : Directory name
    Output        : Prints largest file name and its size
*/
void LargeFile(char *dname)
{
    DIR *dp = NULL;             // Directory stream pointer
    struct dirent *ptr = NULL;  // Directory entry pointer
    struct stat sobj;           // Structure to hold file metadata
    int iRet = 0;
    char path[100];             // Stores full path of file
    int fSize = 0;              //to store size
    char fName[100];

    dp = opendir(dname);

    if(dp == NULL)
    {
        printf("%s\n", strerror(errno));
    }
    else
    {
        printf("Directory gets successfully opened\n");
    }
    
    while(ptr = readdir(dp))
    {        
        snprintf(path, sizeof(path), "%s/%s",dname, ptr->d_name); //IMP lstat requires full path not only name so it will make full path name 

        iRet = lstat(path, &sobj);

        if(iRet == -1)
        {
            perror("Unable to describe lstat");
        }

        if(S_ISREG(sobj.st_mode))
        {   
            if((sobj.st_size) > fSize)
            {
                fSize = sobj.st_size;
                strcpy(fName, ptr->d_name);
            }
        }
    }

    closedir(dp);

    printf("Largest File is : %s\n", fName);
    printf("Size of  File is : %d\n", fSize);
}

int main()
{
    char dname[50];

    printf("Enter directory name : ");
    scanf("%s", dname);

    LargeFile(dname);

    return 0;
}