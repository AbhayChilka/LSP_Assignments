/*2.3  List all FIles from Directory
    > Accept directory name
    > Use opendir() / readdir() to print only names(skip . nad ..)
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
    DIR *dp = NULL;
    char dname[50];

    struct dirent *ptr = NULL;

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
        printf("%s\n",ptr->d_name );           
    }

    closedir(dp);

    return 0;
}