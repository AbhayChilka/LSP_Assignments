/*
    * 2.4  List all FIles from Directory with type *
    > Accept directory name
    > Print each entry with its types: Regular/Directory/Link/FIFO/Socket/Char/Block
    > Use lstat() for accurate type
*/

/*
    lstat()
    -------
    Retrieves information about a file or symbolic link.
    Unlike stat(), lstat() does NOT follow symbolic links.
    It returns metadata of the link itself if the file is a symlink.

    Parameters:
        path   : Full path of the file
        sb     : Pointer to struct stat to store file information

    Return Value:
        0   -> Success
       -1   -> Failure (errno is set)

    Used when accurate file type detection is required.
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

    while(ptr = readdir(dp))
    {
        if(strcmp(ptr->d_name, ".") == 0 || strcmp(ptr->d_name, "..") == 0)
        {
            continue;
        }
        printf("%s\n",ptr->d_name );       
        
        snprintf(path, sizeof(path), "%s/%s",dname, ptr->d_name); //IMP lstat requires full path not only name so it will make full path name 

        printf("%s : File type is -", ptr->d_name);

        iRet = lstat(path, &sobj);

        if(iRet == -1)
        {
            perror("Unable to describe lstat");
        }

        if(S_ISBLK(sobj.st_mode))
        {
            printf("Block Device\n");
        }
        else if(S_ISCHR(sobj.st_mode))
        {
            printf("Character Device\n");
        }
        else if(S_ISDIR(sobj.st_mode))
        {
            printf("Directory File\n");
        }
        else if (S_ISREG(sobj.st_mode))
        {
            printf("Regular File\n");
        }
        else if (S_ISSOCK(sobj.st_mode))
        {
            printf("Socket File\n");
        }
        else if(S_ISFIFO(sobj.st_mode))
        {
            printf("Pipe File\n");
        }
        else if(S_ISLNK(sobj.st_mode))
        {
            printf("Symbolic File\n");
        }        
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