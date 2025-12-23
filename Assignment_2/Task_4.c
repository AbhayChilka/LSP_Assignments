/*2.4  List all FIles from Directory with type
    > Accept directory name
    > Print each entry with its types: Regular/Directory/Link/FIFO/Socket/Char/Block
    > Use lstat() for accurate type
*/

#include<unistd.h>
#include<stdio.h>
#include<fcntl.h>
#include<string.h>
#include<errno.h>
#include<sys/stat.h>
#include<dirent.h>
#include<sys/types.h>

int main()
{
    DIR *dp = NULL;       //for open dir
    char dname[50];
    struct dirent *ptr = NULL; //read dir
    struct stat sobj;       //for stat of dir
    int iRet = 0;
    char path[100];

    printf("Enter directory name : ");
    scanf("%s", dname);

    dp = opendir(dname);

    if(dp == NULL)
    {
        printf("%s\n", strerror(errno));
        return -1;
    }
    else
    {
        printf("Directory gets successfully opened\n");
    }
    
    printf("File from directory are :\n");
    while(ptr = readdir(dp))
    {
        if(strcmp(ptr->d_name, ".") == 0 || strcmp(ptr->d_name, "..") == 0)
        {
            continue;
        }
        
        snprintf(path, sizeof(path), "%s/%s",dname, ptr->d_name); //IMP lstat requires full path not only name so it will make full path name 

        printf("%s : File type is -", ptr->d_name);

        iRet = lstat(path, &sobj);

        if(iRet == -1)
        {
            perror("Unable to describe lstat");
        }

        if(S_ISBLK(sobj.st_mode))
        {
            printf("Block Device\n");
        }
        else if(S_ISCHR(sobj.st_mode))
        {
            printf("Character Device\n");
        }
        else if(S_ISDIR(sobj.st_mode))
        {
            printf("Directory File\n");
        }
        else if (S_ISREG(sobj.st_mode))
        {
            printf("Regular File\n");
        }
        else if (S_ISSOCK(sobj.st_mode))
        {
            printf("Socket File\n");
        }
        else if(S_ISFIFO(sobj.st_mode))
        {
            printf("Pipe File\n");
        }
        else if(S_ISLNK(sobj.st_mode))
        {
            printf("Symbolic File\n");
        }

    }

    closedir(dp);

    return 0;
}