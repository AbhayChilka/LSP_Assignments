/*
    * 3.2  Check File present in Directory *
    > Accept directory name and file name
    > Check whether that file exists in that directory
    > Print absolute matched path if found
*/

/*
    realpath()
    ----------
    Syntax:
        #include <stdlib.h>
        char *realpath(const char *path, char *resolved_path);

    Description:
        Resolves a file path to its absolute, canonical form.
        Removes '.', '..' and resolves symbolic links.

    Parameters:
        path           : Relative or absolute file path
        resolved_path  : Buffer to store resolved absolute path (or NULL for dynamic allocation)

    Return Value:
        Non-NULL -> Success (pointer to resolved path)
        NULL     -> Failure (errno is set)

    Used for path normalization and symlink resolution.
*/

#include<stdio.h>   // Standard I/O functions like printf()
#include<fcntl.h>   // File control options: open(), O_RDONLY, O_WRONLY
#include<errno.h>   // For errno variable and error codes
#include<unistd.h>  // Provides POSIX system calls: read(), write(), close()
#include<string.h> // String handling functions like strlen(), strcpy(), strcmp(), memset()
#include<sys/stat.h> // Provides definitions for file metadata (struct stat) and functions like stat(), lstat(), fstat()
#include<dirent.h>   // Directory handling functions and structures: opendir(), readdir(), closedir(), struct dirent
#include<sys/types.h>  // Defines system data types used by system calls such as pid_t, size_t, off_t, ino_t
#include <linux/limits.h>   // PATH_MAX
#include<stdlib.h>          // realpath()

/*
    Function Name : CheckFile
    Description   : Checks whether a file exists in a given directory
    Input         : dname -> directory name , fname -> file
    Return Value  : 0  -> file found
                   -1  -> file not found / error
*/
int CheckFile(char *dname, char *fname)
{
    DIR *dp = NULL;             // Directory stream pointer
    struct dirent *ptr = NULL;  // Directory entry pointer
    int iRet = 0;
    int found = 0;
    char path[PATH_MAX];        // Stores full path of file
    char abpath[PATH_MAX];     // Stores absolute path

    dp = opendir(dname);

    if(dp == NULL)
    {
        printf("%s\n", strerror(errno));
        return -1;
    }
    else
    {
        printf("Directory gets successfully opened\n");
    }

    while(ptr = readdir(dp))
    {
        if(strcmp(ptr->d_name,fname) == 0)
        {
            found = 1;
            printf("File is present\n");

            snprintf(path, sizeof(path), "%s/%s", dname, fname); // Create path: directory + filename

            if(realpath(path, abpath) != NULL) // Convert to absolute path
            {
                printf("Absolute Path: %s\n", abpath);
            }
            else
            {
                perror("realpath");
            }
            
            break;
        }
    }    

    closedir(dp);

    if(found == 0)
    {
        printf("File not present in directory");

        return -1;
    }

    return 0;
}

int main()
{
    char dname[50];
    char fname[50];

    printf("Enter directory name : ");
    scanf("%s", dname);

    printf("Enter file name : ");
    scanf("%s", fname);

    CheckFile(dname, fname);

    return 0;
}