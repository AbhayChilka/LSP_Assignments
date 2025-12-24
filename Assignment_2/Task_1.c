/*
    * 2.1 Read Whole File *
    > Accept file name and print full content on console
    > Use a buffer loop (read() until 0)
    >  Show total bytes read
*/

/*
    Function Name : ReadFile
    Description   : Reads entire file content using read() system call
                    until End Of File (EOF) is reached
    Input         : Name of the file to read
    Return Value  : None
*/

#include<stdio.h>   // Standard I/O functions like printf()
#include<fcntl.h>   // File control options: open(), O_RDONLY, O_WRONLY
#include<errno.h>   // For errno variable and error codes
#include<unistd.h>  // Provides POSIX system calls: read(), write(), close()
#include<string.h> // String handling functions like strlen(), strcpy(), strcmp(), memset()

#define SIZE_BUFFER 100

void ReadFile(char *fname)
{
    int fd = 0;
    char Buffer[SIZE_BUFFER + 1];
    int iRet = 0;
    int No = 0;

    //Initialize buffer with NULL characters
    memset(Buffer, '\0', SIZE_BUFFER);

    // Open file in read-only mode
    fd = open(fname, O_RDONLY);

    if (fd == -1)
    {
        printf("Unable to open file\n");
        printf("Reason : %s\n", strerror(errno));
        return;
    }

    printf("File opened successfully with fd : %d\n", fd);

    printf("Data from file is :\n");

    while((iRet = read(fd, Buffer, SIZE_BUFFER)) > 0)
    {
        Buffer[iRet] = '\0';             //NUll termination set last \0 string operation
        printf("%s", Buffer);
        No = No +iRet;
    }

    printf("\n");
    printf("Total bytes gets read are %d\n", No);
    close(fd);

}

int main()
{
    int fd = 0;
    char fname[50];

    printf("Enter file name : ");
    scanf("%s", fname);

    ReadFile(fname);

    return 0;
}