#include<fcntl.h>    //file control
#include<stdio.h>
#include<unistd.h>

int main()
{
    int fd = 0;

    fd = open("Second.c",O_CREAT | O_TRUNC,0777);

    if(fd == -1)
    {
        printf("Unable to create file\n");
    }
    else
    {
        printf("FIle gets successfully created with fd : %d\n", fd);
    }

    close(fd);

    return 0;
}

