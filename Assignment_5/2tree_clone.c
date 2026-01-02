/*
    * Recursive Directory Traversal
    Write tree_clone.c which prints a directory as a tree, like :
    root/
        a.txt
        src/
            Ganesh.c

    > Indentation based on recursion depth
    > Print types markes :
        . [D] directory
        . [F] regular file
        . [L] symbolic link

    > UselStat() to detect symbolic links.
    > Do not follow symlink directories(avoid loops)
*/

#include<stdio.h>   // Standard I/O functions like printf()
#include<fcntl.h>   // File control options: open(), O_RDONLY, O_WRONLY
#include<errno.h>   // For errno variable and error codes
#include<unistd.h>  // Provides POSIX system calls: read(), write(), close()
#include<string.h> // String handling functions like strlen(), strcpy(), strcmp(), memset()
#include<sys/stat.h> // Provides definitions for file metadata (struct stat) and functions like stat(), lstat(), fstat()
#include<dirent.h>   // Directory handling functions and structures: opendir(), readdir(), closedir(), struct dirent
#include<sys/types.h>  // Defines system data types used by system calls such as pid_t, size_t, off_t, ino_t

//helper function for tree style print
void TreeIndentation(int level)
{
    for(int i = 0; i < level; i++)
        printf("        ");
}

/*
    Function Name : TreeDir
    Description   : Check the given directory and print tree style pattern for files and sub-director-inside sub-dir file
                    using recursive call
    Input         : Directory name
    Output        : print directory as tree
*/
void TreeDir(char *dname, int level)
{
    DIR *dp = NULL;             // Directory stream pointer
    struct dirent *ptr = NULL;  // Directory entry pointer
    struct stat sobj;           // Structure to hold file metadata
    int iRet = 0;
    char path[100];             // Stores full path of file
    int printcount = level;

    dp = opendir(dname);

    if(dp == NULL)
    {
        printf("%s\n", strerror(errno));
    }
    
    while(ptr = readdir(dp))
    {        
        if(strcmp(ptr->d_name, ".") == 0 || strcmp(ptr->d_name, "..") == 0)
        {
            continue;
        }

        snprintf(path, sizeof(path), "%s/%s",dname, ptr->d_name); //IMP lstat requires full path not only name so it will make full path name 

        iRet = lstat(path, &sobj);

        if(iRet == -1)
        {
            perror("Unable to describe lstat");
        }

        TreeIndentation(printcount);

        if(S_ISDIR(sobj.st_mode))
        {
            //Note : this is based on lstat(), a symlink directory fails this test.
            /*S_ISLNK == true S_ISDIR == false*/

            printf("|___[D] %s/\n", ptr->d_name);
            TreeDir(path, printcount + 1);         //recursion till inner directory gets
        }
        else if(S_ISREG(sobj.st_mode))
        {
            printf("|___[F] %s\n", ptr->d_name);
        } 
        else if(S_ISLNK(sobj.st_mode))
        {
            printf("|___[S] %s\n", ptr->d_name);            
        }
    }

    closedir(dp);
}

int main()
{
    char dname[50];

    printf("Enter directory name : ");
    scanf("%s", dname);

    printf("%s/\n", dname);
    TreeDir(dname, 0);

    return 0;
}