/*
    * 3.1 Copy File contents(source -> destination) *
    > Accept source_file and dest_file
    > Create destination if not exists (O_CREAT | O_TRUNC)
    > Copy using buffered read() / write() loop
    > Preserve permission (optional bonus using stat() + chmode())
*/

#include<stdio.h>   // Standard I/O functions like printf()
#include<fcntl.h>   // File control options: open(), O_RDONLY, O_WRONLY
#include<errno.h>   // For errno variable and error codes
#include<unistd.h>  // Provides POSIX system calls: read(), write(), close()
#include<string.h> // String handling functions like strlen(), strcpy(), strcmp(), memset()
#include<sys/stat.h> // Provides definitions for file metadata (struct stat) and functions like stat(), lstat(), fstat()
#include<dirent.h>   // Directory handling functions and structures: opendir(), readdir(), closedir(), struct dirent
#include<sys/types.h>  // Defines system data types used by system calls such as pid_t, size_t, off_t, ino_t

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
    int No = 0;

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
        No = No+iWrite;
    }

    printf("Total bytes gets read are %d\n", No);
 
    close(fd1);
    close(fd2);
}

int main()
{
    char sFIle[50];
    char dFile[50];

    printf("Enter Source File :");
    scanf("%s", sFIle);

    printf("Enter destination file : ");
    scanf("%s", dFile);

    CopyFile(sFIle, dFile);
    
    return 0;
}