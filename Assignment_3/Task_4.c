/*
    * 3.4 Delete all Empty files *
    > Accept directory name
    > Delete files witj size = 0 bytes (regular files only)
    > Print names deleted + total deleted count 
*/

/*
    remove()
    --------
    Deletes a file from the filesystem.
    For regular files, it internally calls the unlink() system call.
    The file is removed by deleting its directory entry.

    Parameters:
        path   : Path of the file to be deleted

    Return Value:
        0   -> Success
       -1   -> Failure (errno is set)

    Used to delete files programmatically.
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
    Function Name : DelEmpFile
    Description   : Deletes all empty regular files (size = 0 bytes)from the given directory.
    Input         : Directory name
    Output        : Prints deleted file names and total deleted count
*/
void DelEmpFile(char *dname)
{
    DIR *dp = NULL;             // Directory stream pointer
    struct dirent *ptr = NULL;  // Directory entry pointer
    struct stat sobj;           // Structure to hold file metadata
    int iRet = 0;
    char path[100];             // Stores full path of file
    int fCount = 0;             //to store count

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
        if(strcmp(ptr->d_name, ".") == 0 || strcmp(ptr->d_name, "..") == 0)
        {
            continue;
        }

        snprintf(path, sizeof(path), "%s/%s",dname, ptr->d_name); //IMP lstat requires full path not only name so it will make full path name 

        iRet = lstat(path, &sobj);

        if(iRet == -1)
        {
            perror("Unable to describe lstat");
        }

        if(S_ISREG(sobj.st_mode))
        {   
            if((sobj.st_size) == 0)
            {
                fCount++;
                printf("%s file gets deleted\n", path);
                remove(path);
            }
            else
            {
                printf("There are no empty files\n");
            }
        }
    }
    closedir(dp);

    printf("%d files are gets deleted\n", fCount);
}

int main()
{
    char dname[50];

    printf("Enter directory name : ");
    scanf("%s", dname);

    DelEmpFile(dname);

    return 0;
}