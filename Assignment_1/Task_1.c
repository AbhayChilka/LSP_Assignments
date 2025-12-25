/* Question =
    * Open File * 
    > Accept file name from user and open it using open()
    > Print: success message + returned file descriptor
    > Handle errors using perror()
*/

/*
    The open() system call opens the file specified by path.

    parameters : open( File name ,Access mode)

    On success, open()return the new file descriptor (a nonnegative integer).  
    On error, -1 is returned and errno is set to indicate the error.
*/

#include<stdio.h>   // Standard I/O functions like printf()
#include<fcntl.h>   // File control options: open(), O_RDONLY, O_WRONLY
#include<errno.h>   // For errno variable and error codes
#include<unistd.h>  // Provides POSIX system calls: read(), write(), close()

/*
    Function Name : OpenFile
    Description   : Opens file in read only mode
    Input         : fname -> file name
    Return Value  : File descriptor on success, -1 on failure
*/
int OpenFile(char *fname)
{
    int fd = 0;

    fd = open(fname, O_RDONLY);

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
    char fname[50];     //file name input 

    printf("Enter file name : ");
    scanf("%s", fname);

    fd = OpenFile(fname);

    if (fd == -1)
    {
        return -1;
    }
    else
    {
        printf("File is successfully open with fd : %d\n", fd);
    }

    close(fd);

    return 0;
}