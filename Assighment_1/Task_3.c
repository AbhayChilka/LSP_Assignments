/*  Check File Access Permission
    > Accept file name and mode (read/write/execute)
    > Use access() to check permission for current process
    > Print "Accessible / Not accessible"with reason
*/
#include<stdio.h>
#include<fcntl.h>
#include<errno.h>
#include<unistd.h>

int main()
{
    int fd = 0;
    char fname[50];
    char mode;

    printf("Enter file name : ");
    scanf("%s", fname);

    printf("Check permissions :\n");
    printf("R : Read\n W : Write\n X : Execute\n");

    printf("Enter your choice : ");
    scanf(" %c", &mode);

    switch (mode)
    {
    case 'R':
    case 'r':
        fd = access(fname, R_OK);
        break;

    case 'W':
    case 'w':
        fd = access(fname, W_OK);
        break;

    case 'X':
    case 'x':
        fd = access(fname, X_OK);
        break;
        
    default:
        printf("Invalid mode");
        break;
    }

    if(fd == -1)
    {
        perror("Unable to open file");
        return -1;
    }
    else
    {
        printf("Accessible\n");
    }

    close(fd);

    return 0;
}