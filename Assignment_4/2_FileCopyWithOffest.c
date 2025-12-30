/*
    * File Copy with Offset *
    Problem Statment : 
        Copy a file starting from given byte offset of the source file;

    Input:
        source_file, destination_file, offset;

    Output:
        Partialfile copied starting from offset;
*/

/*
    lseek() System Call
    -------------------
    > Used to change the current file offset of an open file
    > It does NOT read or write data
    > Allows random access within a file

    Syntax:
        off_t lseek(int fd, off_t offset, int whence);

    Parameters:
        fd      : File descriptor of an open file
        offset  : Number of bytes to move
        whence  : Reference position
                  SEEK_SET → Beginning of file
                  SEEK_CUR → Current position
                  SEEK_END → End of file

    Return Value:
        On success → New file offset (in bytes)
        On failure → -1

    Uses:
        > Skip bytes in a file
        > Read file from a specific position
        > Append or overwrite data
*/

#include<stdio.h>   // Standard I/O functions like printf()
#include<fcntl.h>   // File control options: open(), O_RDONLY, O_WRONLY
#include<errno.h>   // For errno variable and error codes
#include<unistd.h>  // Provides POSIX system calls: read(), write(), close()
#include<string.h> // String handling functions like strlen(), strcpy(), strcmp(), memset()

#define SIZE_BUFFER 100

/*
  Function Name : CopyFile
  Description   : Copies the contents of source file into destination file from given offset
  Input         : sFile - name of source file (read mode)
                    dFile - name of destination file (write mode)
  Output        : Copies data from source file to destination file
*/
void CopyFile(char *sFile, char *dFile, int offset)
{
    int fd1 = 0;
    int fd2 = 0;
    char Buffer[SIZE_BUFFER];
    int iRead = 0;
    int iWrite = 0;
    int countoffset = 0;

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

    countoffset = lseek(fd1,offset,SEEK_SET);
    if (countoffset == -1)
    {
        perror("lseek failed");
    }

    while((iRead = read(fd1, Buffer, SIZE_BUFFER)) > 0)    //loop for to read source file
    {
        iWrite = write(fd2, Buffer, iRead);     //write data from source file to destination file 
 
        if (iWrite == -1)
        {
            perror("write failed");
            break;
        }
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
    int offset = 0;

    printf("Enter Source File :");
    scanf("%s", sFile);

    printf("Enter destination file : ");
    scanf("%s", dFile);

    printf("Enter offset from which file should copy : ");
    scanf("%d", &offset);

    CopyFile(sFile, dFile, offset);
    
    return 0;
}