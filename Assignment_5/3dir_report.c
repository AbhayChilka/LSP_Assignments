/*
    * File Counter + Size Report
    Create dir_report.cthat recursively calculates :
    > Total number of files
    > Total number of directories
    > Total size of regular files(in bytes)
    > Largest file name + size
    > Count a directory when you enter it
    > For size: consider only regular files(S_ISREG)
    > Ignore symlink target size (treat symlink as link object only)
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
    Function Name : DirRepo
    Description   : Check the given directory and print tree style pattern for files and sub-director-inside sub-dir file
                    using recursive call
    Input         : Directory name
    Output        : print directory as tree
*/
int DirRepo(char *dname)
{
    DIR *dp = NULL;             // Directory stream pointer
    struct dirent *ptr = NULL;  // Directory entry pointer
    struct stat sobj;           // Structure to hold file metadata
    int iRet = 0;
    char path[100];             // Stores full path of file
    int dCount = 0;
    int filecount = 0;

    dp = opendir(dname);

    if(dp == NULL)
    {
        printf("%s\n", strerror(errno));
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

        if(S_ISDIR(sobj.st_mode))
        {
            filecount += DirRepo(path);  //The recursive call returns the count of files in the subdirectory, and the parent accumulates it using +=
        }
        
        if(S_ISREG(sobj.st_mode))
        {
            filecount++;
        }
    }

    closedir(dp);

    return filecount;
    
}

int main()
{
    char dname[50];
    int iCount = 0;

    printf("Enter directory name : ");
    scanf("%s", dname);

    iCount = DirRepo(dname);

    printf("Files : %d", iCount);

    return 0;
}