/*
    * 2.3  List all FIles from Directory *
    > Accept directory name
    > Use opendir() / readdir() to print only names(skip . nad ..)
*/

/*
    opendir() system call
    ---------------------
    The opendir() function opens a directory stream corresponding
    to the directory name specified by the path.

    Syntax:
        DIR *opendir(const char *path);

    Parameters:
        path : Path of the directory to be opened

    Return Value:
        Non-NULL -> Pointer to DIR structure on success
        NULL     -> Failure (errno is set)

    Notes:
        - The returned DIR pointer represents an open directory stream.
        - It must be closed using closedir() after use.
        - opendir() does NOT open files; it opens directories only.
*/

/*
    readdir() system call
    ---------------------
    The readdir() function reads the next directory entry
    from an open directory stream.

    Syntax:
        struct dirent *readdir(DIR *dirp);

    Parameters:
        dirp : Pointer to an open directory stream (DIR *)

    Return Value:
        Non-NULL -> Pointer to struct dirent containing entry information
        NULL     -> End of directory or error occurred

    Information Available in struct dirent:
        d_name : Name of the directory entry (file/subdirectory)
        d_ino  : Inode number of the entry

    Notes:
        - readdir() reads entries sequentially.
        - Entries "." (current) and ".." (parent) are also returned.
        - readdir() returns NULL when no more entries are available.
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
    Function Name : ListFiles
    Description   : Lists all files from given directory using opendir() and readdir()
                    Skips current (.) and parent (..) directory entries
    Input         : dname -> directory name
    Return Value  : None
*/
void ListFiles(char *dname)
{
    DIR *dp = NULL;             // Directory stream pointer
    struct dirent *ptr = NULL;  // Directory entry pointer

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
    }

    closedir(dp);
}

int main()
{
    char dname[50];


    printf("Enter directory name : ");
    scanf("%s", dname);

    ListFiles(dname);

    return 0;
}