#include<fcntl.h>    //file control
#include<stdio.h>

int main(int argc,char *argv[])
{
    int fd = 0;

    fd = creat(argv[1],0777);

    if(fd == -1)
    {
        printf("Unble to create file...\n");
    }
    else
    {
        printf("File gets successfully created with fd : %d\n",fd);
    }
  
    
    return 0;
}

