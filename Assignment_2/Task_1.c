/*2.1 Read Whole File
    > Accept file name and print full content on console
    > Use a buffer loop (read() until 0)
    >  Show total bytes read
*/

#include<unistd.h>
#include<stdio.h>
#include<fcntl.h>
#include<string.h>
#include<errno.h>

#define SIZE_BUFFER 100

int main()
{
    int fd = 0;
    char fname[50];
    char Buffer[SIZE_BUFFER + 1];
    int iRet = 0;
    int No = 0;

    memset(Buffer, '\0', SIZE_BUFFER);     

    printf("Enter file name : ");
    scanf("%s", fname);

    fd = open(fname, O_RDONLY);

    if(fd < 0)
    {
        printf("Unable to open the file\n");
        printf("Reason : %s\n", strerror(errno));
        return -1;
    }

    printf("File successfully open with fd : %d\n", fd);

    printf("Data from file is :\n");

    while((iRet = read(fd, Buffer, SIZE_BUFFER)) > 0)
    {
        Buffer[iRet] = '\0';             //NUll termination set last \0 string operation
        printf("%s", Buffer);
        No = No +iRet;
    }

    printf("Total bytes gets read are %d\n", No);
    close(fd);

    return 0;
}
