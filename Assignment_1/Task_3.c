/*  Question =
    * Check File Access Permission *
    > Accept file name and mode (read/write/execute)
    > Use access() to check permission for current process
    > Print "Accessible / Not accessible"with reason
*/

/*
    The access() system call checks the calling process's permissions
    for a file specified by the given pathname. 
    
    int access(const char *pathname, int mode);

    parametrs = file name, mode

    Returns = 0 - Requested access is permitted
       -1 = Access denied or file does not exist (errno is set)

    Note:
        access() does NOT open the file.
        It only checks permissions based on real UID/GID
        of the calling process.
    access() checks file permission without opening the file
*/

#include<stdio.h>   // Standard I/O functions like printf()
#include<fcntl.h>   // File control options: open(), O_RDONLY, O_WRONLY
#include<errno.h>   // For errno variable and error codes
#include<unistd.h>  // Provides POSIX system calls: read(), write(), close()

/*
    Function Name : FileAccess
    Description   : Checks file permission using access() system call
    Input         : file name,
                    mode  -> (R_OK / W_OK / X_OK)
    Return Value  : 0 success, -1 on failure
*/
int FileAccess(char fname[], char mode)
{
    int fd = -1;

    switch (mode)
    {
    case 'R':
    case 'r':
        fd = access(fname, R_OK); //  R_OK -> Check read permission
        break;

    case 'W':
    case 'w':
        fd = access(fname, W_OK); //W_OK -> Check write permission
        break;

    case 'X':
    case 'x':
        fd = access(fname, X_OK); //X_OK -> Check execute permission
        break;
        
    default:
        printf("Invalid mode");
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
    char mode;

    printf("Enter file name : ");
    scanf("%s", fname);

    printf("Check permissions :\n");
    printf("R : Read\n W : Write\n X : Execute\n");

    printf("Enter your choice : ");
    scanf(" %c", &mode);

    fd = FileAccess(fname, mode);

    if(fd == -1)
    {
        perror("Unable to open file");
        return -1;
    }
    else
    {
        printf("Accessible for given mode\n");
    }

    close(fd);

    return 0;
}