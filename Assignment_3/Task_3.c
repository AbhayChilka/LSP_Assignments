/*
    * 3.3 Move all files(Dir -> Dir) *
    > Accept source dir and destination dir
    > Move all regular files:
        . Use rename() if same filesystem
        . Else copy+ delete
    > Print count of moved files
*/

#include<stdio.h>   // Standard I/O functions like printf()
#include<fcntl.h>   // File control options: open(), O_RDONLY, O_WRONLY
#include<errno.h>   // For errno variable and error codes
#include<unistd.h>  // Provides POSIX system calls: read(), write(), close()
#include<string.h> // String handling functions like strlen(), strcpy(), strcmp(), memset()
#include<sys/stat.h> // Provides definitions for file metadata (struct stat) and functions like stat(), lstat(), fstat()
#include<dirent.h>   // Directory handling functions and structures: opendir(), readdir(), closedir(), struct dirent
#include<sys/types.h>  // Defines system data types used by system calls such as pid_t, size_t, off_t, ino_t

/*
    Function Name : MovFileToDir
    Description   : 
    Input         : 
    Output        : 
*/
void MovFileToDir(char *sdname, char *ddname)
{
    DIR *sourcedp = NULL;         // Directory stream pointer
    struct dirent *sptr = NULL;   // Directory entry pointer
    struct stat ssobj;           // Structure to hold file metadata
    int iRet1 = 0;

    DIR *destdp = NULL;         // Directory stream pointer
    struct dirent *dptr = NULL;   // Directory entry pointer
    struct stat dsobj;           // Structure to hold file metadata
    int iRet2 = 0;

    char path[100];             // Stores full path of file
    int fCount = 0;             //to store count

    sourcedp = opendir(sdname);

    if(sourcedp == NULL)
    {
        printf("%s\n", strerror(errno));
    }
    else
    {
        printf("Source Directory gets successfully opened\n");
    }

    destdp = opendir(ddname);

    if(destdp == NULL)
    {
        printf("%s\n", strerror(errno));
    }
    else
    {
        printf("Destination Directory gets successfully opened\n");
    }


/*    while(sptr = readdir(sourcedp))
    {        
        if(strcmp(sptr->d_name, ".") == 0 || strcmp(sptr->d_name, "..") == 0)
        {
            continue;
        }

        snprintf(path, sizeof(path), "%s/%s",sdname, sptr->d_name); //IMP lstat requires full path not only name so it will make full path name 

        iRet1 = lstat(path, &ssobj);

        if(iRet1 == -1)
        {
            perror("Unable to describe lstat");
        }

        if(S_ISREG(ssobj.st_mode))
        {   
    
        }
    }
*/
    closedir(sourcedp);
    closedir(destdp);

}

int main()
{
    char sdname[50];
    char ddname[50];

    printf("Enter source directory name : ");
    scanf("%s", sdname);

    printf("Enter destination directory name : ");
    scanf("%s", ddname);

    MovFileToDir(sdname, ddname);

    return 0;
}