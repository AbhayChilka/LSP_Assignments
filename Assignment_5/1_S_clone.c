/*
  * 1 Director traversal basics *
    Create a program 1s_clone.c that takes one directory path and prints:
        > Entry name
        > Type (file/dir/link/other)
        > Size(bytes)
        > Permissionsin rwxr-xr-x format
        > Last modified time 
        > Skip . and ..
        > Buildfullpath using snprintf(dir + "/" + name) 
*/

#include<stdio.h>   // Standard I/O functions like printf()
#include<fcntl.h>   // File control options: open(), O_RDONLY, O_WRONLY
#include<errno.h>   // For errno variable and error codes
#include<unistd.h>  // Provides POSIX system calls: read(), write(), close()
#include<string.h> // String handling functions like strlen(), strcpy(), strcmp(), memset()
#include<sys/stat.h> // Provides definitions for file metadata (struct stat) and functions like stat(), lstat(), fstat()
#include<dirent.h>   // Directory handling functions and structures: opendir(), readdir(), closedir(), struct dirent
#include<sys/types.h>  // Defines system data types used by system calls such as pid_t, size_t, off_t, ino_t
#include<time.h>

/*
    Function Name : ListFilesTypes
    Description   : Lists all files from a directory along with their types
                    (Regular, Directory, Link, FIFO, Socket, Char, Block)
    Input         : dname -> directory name
    Return Value  : None
*/
void ListFilesTypes(char *dname)
{
    DIR *dp = NULL;             // Directory stream pointer
    struct dirent *ptr = NULL;  // Directory entry pointer
    struct stat sobj;           // Structure to hold file metadata
    int iRet = 0;
    char path[100];             // Stores full path of file

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
    
    printf("File from directory are :\n");
    printf("---------------------------------------------------------\n");

    while(ptr = readdir(dp))
    {
        if(strcmp(ptr->d_name, ".") == 0 || strcmp(ptr->d_name, "..") == 0)
        {
            continue;
        }
        
        snprintf(path, sizeof(path), "%s/%s",dname, ptr->d_name); //IMP lstat requires full path not only name so it will make full path name 

        printf("File name           : %s\n", ptr->d_name);

        iRet = lstat(path, &sobj);

        if(iRet == -1)
        {
            perror("Unable to describe lstat");
        }

        printf("Type                : ");
        if(S_ISREG(sobj.st_mode))     
        {
             printf("File\n");
        }
        else if(S_ISDIR(sobj.st_mode)) 
        {
            printf("Directory\n");
        }
        else if(S_ISLNK(sobj.st_mode)) 
        {
            printf("Symbolic Link\n");
        }
        else    
        {                       
            printf("Other\n");
        }

        printf("Sizeof file         : %ld\n", sobj.st_size);
        printf("File Permission     : ");
        printf((sobj.st_mode & S_IRUSR) ? "r" : "-");
        printf((sobj.st_mode & S_IWUSR) ? "w" : "-");
        printf((sobj.st_mode & S_IXUSR) ? "x" : "-");
        printf((sobj.st_mode & S_IRGRP) ? "r" : "-");
        printf((sobj.st_mode & S_IWGRP) ? "w" : "-");
        printf((sobj.st_mode & S_IXGRP) ? "x" : "-");
        printf((sobj.st_mode & S_IROTH) ? "r" : "-");
        printf((sobj.st_mode & S_IWOTH) ? "w" : "-");
        printf((sobj.st_mode & S_IXOTH) ? "x" : "-");
        printf("\n");
        printf("Last Modify Time    : %s", ctime(&sobj.st_mtime));
        printf("---------------------------------------------------------\n");
    }

    closedir(dp);
}

int main()
{
    char dname[50];

    printf("Enter directory name : ");
    scanf("%s", dname);

    ListFilesTypes(dname);

    return 0;
}