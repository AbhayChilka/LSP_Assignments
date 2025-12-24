/* Question =
    * Read N bytes from file * 
    > Accept file name andnumber of bytes N
    > Read exactly N bytes using read() and print on console
    > if file contains less than N, print only available bytes
*/

/*
    The read() system call is used to read data from an open file
    referenced by a file descriptor.

    read(int fd, void *buffer, size_t count);

    Parameters:
        fd     : File descriptor of the open file
        buffer : Memory area where the read data will be stored
        count  : Number of bytes requested to read    
    
        Return Value:
        > 0  : Number of bytes actually read
        = 0  : End of file reached
        -1   : Error occurred

    Notes:
        - read() does NOT append a NULL ('\\0') character.
        - It may return fewer bytes than requested.
        - Actual bytes read depend on file size and EOF.        
*/


#include<stdio.h>   // Standard I/O functions like printf()
#include<fcntl.h>   // File control options: open(), O_RDONLY, O_WRONLY
#include<errno.h>   // For errno variable and error codes
#include<unistd.h>  // Provides POSIX system calls: read(), write(), close()
#include<string.h> // String handling functions like strlen(), strcpy(), strcmp(), memset()

#define BUFFER_NO 100

/*
    Function Name : ReadData
    Description   : Reads N bytes from a given file and prints on console
    Input         : file name,
                    bytes -> number of bytes to read
    Return Value  : None
*/
void ReadData(char *fname, int bytes)
{
    int fd = 0;
    int iRet = 0;
    char Buffer[BUFFER_NO];

    //Initialize buffer with NULL characters
    memset(Buffer, '\0', BUFFER_NO);

    // Open file in read-only mode
    fd = open(fname, O_RDONLY);

    if (fd == -1)
    {
        printf("Unable to open file\n");
        printf("Reason : %s\n", strerror(errno));
        return;
    }

    printf("File opened successfully with fd : %d\n", fd);

    // Prevent buffer overflow
    if (bytes >= BUFFER_NO)
    {
        bytes = BUFFER_NO - 1;
    }

    iRet = read(fd, Buffer, bytes);

    if (iRet == -1)
    {
        perror("read failed");
        close(fd);
        return;
    }

    printf("Number of bytes read : %d\n", iRet);
    printf("Data from file :\n%s\n", Buffer); 
    
    close(fd);
}

int main()
{
    char fname[50];
    int bytes = 0;

    printf("Enter file name : ");
    scanf("%s", fname);

    printf("Enter how many bytes want to read : ");
    scanf("%d", &bytes);

    ReadData(fname, bytes);

    return 0;
}