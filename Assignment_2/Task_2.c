/*2.2 Write String to File
    > Accept file name and a string from user 
    > Write String using write() (appen mode by default)
    >  Print number of bytes written
*/

#include<unistd.h>
#include<stdio.h>
#include<fcntl.h>
#include<string.h>
#include<errno.h>

#define SIZE_BUFFER 1024

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

    fd = open(fname, O_WRONLY | O_APPEND |O_CREAT, 0777);

    if(fd < 0)
    {
        printf("Unable to open the file\n");
        printf("Reason : %s\n", strerror(errno));
        return -1;
    }

    printf("File successfully open with fd : %d\n", fd);

    iRet = write(fd, Buffer, strlen(Buffer));

    printf("%d bytes gets write\n", iRet);

    close(fd);

    return 0;
}
