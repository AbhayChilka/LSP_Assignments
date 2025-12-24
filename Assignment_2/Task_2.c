/*
    * 2.2 Write String to File *
    > Accept file name and a string from user 
    > Write String using write() (appen mode by default)
    >  Print number of bytes written
*/

/*
    The write() system call is used to write data to an open file
    referenced by a file descriptor.

    Syntax:
         write(int fd, const void *buffer, size_t count);

    Parameters:
        fd     : File descriptor of the open file
        buffer : Memory area containing data to be written
        count  : Number of bytes to write from buffer

    Return Value:
        > 0  : Number of bytes actually written
        = 0  : No bytes written
        -1   : Error occurred (errno is set)

    Notes:
        - write() writes raw bytes; it does NOT append a NULL ('\\0') character.
        - It may write fewer bytes than requested.
        - Actual behavior depends on file type and system conditions.
*/    



#include<stdio.h>   // Standard I/O functions like printf()
#include<fcntl.h>   // File control options: open(), O_RDONLY, O_WRONLY
#include<errno.h>   // For errno variable and error codes
#include<unistd.h>  // Provides POSIX system calls: read(), write(), close()
#include<string.h> // String handling functions like strlen(), strcpy(), strcmp(), memset()

#define SIZE_BUFFER 1024

/*
    Function Name : WriteStr
    Description   : Writes a user-provided string into a file using write()
                    File is opened in append mode
    Input         : fname  -> file name
                    Buffer -> string to write
    Return Value  : Number of bytes written on success, -1 on failure
*/
int WriteStr(char * fname, char *Buffer)
{
    int fd = 0;
    int iRet = 0;

    fd = open(fname, O_WRONLY | O_APPEND |O_CREAT, 0777); // Open file in write + append mode (create if file does not exist)

    if(fd < 0)
    {
        printf("Unable to open the file\n");
        printf("Reason : %s\n", strerror(errno));
        return -1;
    }

    printf("File successfully open with fd : %d\n", fd);

    iRet = write(fd, Buffer, strlen(Buffer));

    if (iRet == -1)
    {
        perror("write failed");
        close(fd);
        return -1;
    }

    close(fd);

    return fd;
}

int main()
{
    int fd = 0;
    char fname[50];
    char Buffer[SIZE_BUFFER];
    int iRet = 0;

    printf("Enter file name : ");
    scanf("%s", fname);

    printf("Enter string : ");
    scanf(" %1023[^\n]s", Buffer);

    iRet = WriteStr(fname,Buffer);

    printf("%d bytes gets write\n", iRet);

    return 0;
}
