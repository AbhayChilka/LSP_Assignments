#include<unistd.h>
#include<stdio.h>
#include<fcntl.h>
#include<string.h>
#include<errno.h>

#define SIZE_BUFFER 100

int main()
{
    int fd = 0;
    char Buffer[SIZE_BUFFER];
    int iRet = 0;

    memset(Buffer, '\0', SIZE_BUFFER);     

    fd = open("Demo.txt", O_RDONLY);

    if(fd < 0)
    {
        printf("Unable to open the file\n");
        printf("Reason : %s\n", strerror(errno));
        return -1;
    }

    printf("File successfully open with fd : %d\n", fd);

    iRet = read(fd, Buffer,10);      
     
    printf("%d bytes gets successfully read\n", iRet);

    printf("Data from file : %s\n", Buffer);

    close(fd);

    fd = open("Demo.txt", O_RDONLY);    //IMP

    memset(Buffer, '\0', SIZE_BUFFER);    

    iRet = read(fd, Buffer,10);      
     
    printf("%d bytes gets successfully read\n", iRet);

    printf("Data from file : %s\n", Buffer);

    close(fd);

    return 0;
}
