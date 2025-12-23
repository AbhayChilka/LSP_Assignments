/* Question = 
    * Display Complete File Information *
    > Accept file name and display file metadata using stat()
    > Size, inode, permissions, hard link, owner uid/gid, file type, last access/modify time
*/

/*
    stat() retrieve information about the file pointed to by path;

    Syntax:
        int stat(const char *pathname, struct stat *statbuf);

    Parameters:
        pathname : Name (path) of the file whose information is required
        statbuf  : Pointer to a struct stat object that will be filled
                   with file information

    Information Provided:
        - File size
        - Inode number
        - File permissions (mode)
        - File type (regular, directory, link, etc.)
        - Number of hard links
        - Owner UID and GID
        - Last access, modification, and status change times

    Return Value:
        0  -> Success (stat structure is filled)
       -1  -> Failure (errno is set appropriately)

    Note:
        stat() follows symbolic links and returns information
        about the target file, not the link itself.    
*/

/*
    Function Name : FileInfo
    Description   : Displays complete metadata of a file using stat()
    Input         : fname -> file name
    Return Value  : None
*/

#include<stdio.h>   // Standard I/O functions like printf()
#include<fcntl.h>   // File control options: open(), O_RDONLY, O_WRONLY
#include<errno.h>   // For errno variable and error codes
#include<unistd.h>  // Provides POSIX system calls: read(), write(), close()
#include<sys/stat.h> // Provides definitions for file metadata (struct stat) and functions like stat(), lstat(), fstat()

void FileInfo(char *fname)
{
    struct stat sobj;

    int iRet = 0;

    // Get file information
    iRet = stat(fname, &sobj);

    if (iRet == -1)
    {
        perror("stat failed");
        return;
    }

    printf("\n----- File Information -----\n");
    printf("File Size           : %lu bytes\n", sobj.st_size);
    printf("Inode Number        : %lu\n", sobj.st_ino);
    printf("Hard Link Count     : %lu\n", sobj.st_nlink);
    printf("Owner UID           : %u\n", sobj.st_uid);
    printf("Owner GID           : %u\n", sobj.st_gid);
    printf("File Mode           : %o\n", sobj.st_mode & 0777);
    printf("Last Access Time    : %lu\n", sobj.st_atime);
    printf("Last Modify Time    : %lu\n", sobj.st_mtime);

}

int main()
{
    char fname[50];

    printf("Enter file name : ");
    scanf("%s", fname);

    FileInfo(fname);

    return 0;
}