/*  Open File in given mode
    > Accept file name and mode (R, W, RW, A)from user
    > Convert mode to flags (O_RDONLY, O_WRONLY, O_RDWR, O_APPEND | O_CREAT)
    > Open file accordingly and display fd;
*/

#include<stdio.h>
#include<fcntl.h>
#include<errno.h>
#include<unistd.h>

int main()
{
    int fd = 0;
    char fname[50];
    char mname;

    printf("Enter file name : ");
    scanf("%s", fname);

    printf("Enter in which mode want to open : \n");
    printf("press R to Read only\n");
    printf("press W to Write only\n");
    printf("press D to ReadandWrite\n");
    printf("press A to Append\n");

    scanf(" %c", &mname);

    switch (mname)
    {
    case 'R':
    case 'r':
        fd = open(fname, O_RDONLY);    
    break;
    
    case 'W':
    case 'w':
        fd = open(fname, O_WRONLY| O_CREAT, 0777);    
    break;

    case 'D':
    case 'd':
        fd = open(fname, O_RDWR| O_CREAT, 0777);    
    break;

    case 'A':
    case 'a':
        fd = open(fname, O_WRONLY | O_APPEND| O_CREAT, 0777);    
    break;

    default:
        printf("No such modes\n");
        return -1;
        break;
    }

    if(fd == -1)
    {
        perror("Unable to open file");
        return -1;
    }
    else
    {
        printf("File is successfully open with fd : %d\n", fd);
    }

    return 0;
}