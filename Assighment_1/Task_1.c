/*  Open File 
    > Accept file name from user and open it using open()
    > Print: success message + returned file descriptor
    > Handle errors using perror()
*/

#include<stdio.h>
#include<fcntl.h>
#include<errno.h>
#include<unistd.h>

int main()
{
    int fd = 0;
    char fname[50];

    printf("Enter file name : ");
    scanf("%s", fname);

    fd = open(fname, O_RDONLY);

    if(fd == -1)
    {
        perror("Unable to open file");
        return -1;
    }
    else
    {
        printf("File is successfully open with fd : %d\n", fd);
    }

    close(fd);

    return 0;
}