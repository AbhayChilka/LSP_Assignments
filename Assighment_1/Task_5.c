/*  Read N bytes from file 
    > Accept file name andnumber of bytes N
    > Read exactly N bytes using read() and print on console
    > if file contains less than N, print only available bytes
*/

#include<stdio.h>
#include<fcntl.h>
#include<errno.h>
#include<unistd.h>
#include<string.h>

#define BUFFER_NO 100

int main()
{
    int fd = 0;
    char fname[50];
    char Buffer[BUFFER_NO];
    int iRet = 0;
    int bytes = 0;

    memset(Buffer, '\0', BUFFER_NO);

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

    printf("Enter how many bytes want to read : ");
    scanf("%d", &bytes);

    if(BUFFER_NO < bytes)
    {
        bytes = BUFFER_NO -1;
    }

    iRet = read(fd, Buffer,bytes);      


    printf("Number of bytes gets read : %d\n", iRet);
    printf("Data from file : %s\n", Buffer);

    close(fd);

    return 0;
}