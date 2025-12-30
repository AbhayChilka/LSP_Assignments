/*
    * File Copy Utility *
    Problem Statment : 
        Write a program that copies the contents of one file into another;

    Input:
        Source file name and destination file name as command-line arguments;

    Output:
        Destination file containing  an exact copy of source file;
        -> Habdle file-not-found and permission errors;
        -> Destination file should be created if not present;
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

    while((iRead = read(fd1, Buffer, SIZE_BUFFER)) > 0)    //loop for to read source file
    {
        iWrite = write(fd2, Buffer, iRead);     //write data from source file to destination file 
    }
 
    close(fd1);
    close(fd2);
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Usage: %s <SourceFile> <DestinationFile>\n", argv[0]);
        return -1;
    }
    
    CopyFile(argv[1], argv[2]);
    
    return 0;
}