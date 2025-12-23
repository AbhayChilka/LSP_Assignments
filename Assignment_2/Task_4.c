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
            
    }

    closedir(dp);

    return 0;
}