/* Question =
    * Open File in given mode *
    > Accept file name and mode (R, W, RW, A)from user
    > Convert mode to flags (O_RDONLY, O_WRONLY, O_RDWR, O_APPEND | O_CREAT)
    > Open file accordingly and display fd;
*/

/*
    The open() system call opens the file specified by path.

    parameters : open( File name ,Access mode)

    On success, open()return the new file descriptor (a nonnegative integer).  
    On error, -1 is returned and errno is set to indicate the error.
*/

/*
    Function Name : OpenFile
    Description   : Opens file in specified mode using open()
    Input         : file name,
                    mode  -> R(Read), W(Write), D(Read+Write), A(Append)
    Return Value  : File descriptor on success, -1 on failure
*/

#include<stdio.h>   // Standard I/O functions like printf()
#include<fcntl.h>   // File control options: open(), O_RDONLY, O_WRONLY
#include<errno.h>   // For errno variable and error codes
#include<unistd.h>  // Provides POSIX system calls: read(), write(), close()


int OpenFile(char fname[], char mode)
{
    int fd = -1;

    switch (mode)
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
        perror("Error while opening file");
        return -1;
    }

    return fd;
}

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

    fd = OpenFile(fname, mname);

    if (fd == -1)
    {
        return -1;
    }
    else
    {
        printf("File is successfully open with fd : %d\n", fd);
    }

    return 0;
}