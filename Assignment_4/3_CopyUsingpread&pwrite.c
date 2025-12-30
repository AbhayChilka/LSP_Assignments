/*
    * File Copy using pread & pwrite *
    Problem Statment : 
        Copy a file using pread() and pwrite() without changing the file offset;

    Input:
        source_file, destination_file;

    Output:
        Copied file identical to source ;
*/

/*
    pread() System Call
    -------------------
    > Used to read data from a file at a specific offset
    > Does NOT change the file offset
    > Safe for multi-process / multi-threaded programs

    Syntax:
        ssize_t pread(int fd, void *buf, size_t count, off_t offset);

    Parameters:
        fd      : File descriptor of an open file
        buf     : Buffer to store read data
        count   : Number of bytes to read
        offset  : Position in file from where data is read

    Return Value:
        On success → Number of bytes read
        On failure → -1

    Advantages:
        > No need to use lseek()
        > Prevents race conditions
        > Atomic read operation
*/

/*
    pwrite() System Call
    --------------------
    > Used to write data to a file at a specific offset
    > Does NOT change the file offset
    > Useful for concurrent file access

    Syntax:
        ssize_t pwrite(int fd, const void *buf, size_t count, off_t offset);

    Parameters:
        fd      : File descriptor of an open file
        buf     : Buffer containing data to write
        count   : Number of bytes to write
        offset  : Position in file where data is written

    Return Value:
        On success → Number of bytes written
        On failure → -1

    Advantages:
        > No need to reposition file pointer
        > Avoids file offset conflicts
        > Atomic write operation
*/

#include<stdio.h>   // Standard I/O functions like printf()
#include<fcntl.h>   // File control options: open(), O_RDONLY, O_WRONLY
#include<errno.h>   // For errno variable and error codes
#include<unistd.h>  // Provides POSIX system calls: read(), write(), close()
#include<string.h> // String handling functions like strlen(), strcpy(), strcmp(), memset()

#define SIZE_BUFFER 100

/*
  Function Name : CopyFile
  Description   : Copies the contents of source file into destination file 
  Input         : sFile - name of source file (read mode)
                    dFile - name of destination file (write mode)
  Output        : Copies data from source file to destination file
*/
void CopyFile(char *sFile, char *dFile)
{
    int fd1 = 0;
    int fd2 = 0;
    char Buffer[SIZE_BUFFER];
    int iRead = 0;
    int iWrite = 0;
    off_t offset = 0;

    fd1 = open(sFile, O_RDONLY);     // Open source file in read-only mode
    if (fd1 == -1)
    {
        printf("Unable to open file\n");
        printf("Reason : %s\n", strerror(errno));
        return;
    }
    printf("Source File opened successfully with fd1 : %d\n", fd1);

    fd2 = open(dFile, O_WRONLY | O_CREAT | O_TRUNC, 0777);     // Open destination file in write-only mode
    if (fd2 == -1)
    {
        printf("Unable to open file\n");
        printf("Reason : %s\n", strerror(errno));
        return;
    }
    printf("Destination File opened successfully with fd2 : %d\n", fd2);

    while((iRead = pread(fd1, Buffer, SIZE_BUFFER, offset)) > 0)    //loop for to read source file
    {
        iWrite = pwrite(fd2, Buffer, iRead, offset);     //write data from source file to destination file 
 
        if (iWrite == -1)
        {
            perror("write failed");
            break;
        }

        offset = offset + iRead;
    }
 
    if (iRead == -1)
    {
        perror("read failed");
    }

    close(fd1);
    close(fd2);
}

int main()
{
    char sFile[50];
    char dFile[50];

    printf("Enter Source File :");
    scanf("%s", sFile);

    printf("Enter destination file : ");
    scanf("%s", dFile);

    CopyFile(sFile, dFile);
    
    return 0;
}