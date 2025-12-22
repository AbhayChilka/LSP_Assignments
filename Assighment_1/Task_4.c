/*  Display Complete File Information
    > Accept file name and display file metadata using stat()
    > Size, inode, permissions, hard link, owner uid/gid, file type, last access/modify time
*/

#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>    //file control
#include<sys/stat.h>

int main()
{
    struct stat sobj;
    int iRet = 0;
    char fname[50];

    printf("Enter file name : ");
    scanf("%s", fname);

    iRet = stat(fname, &sobj);

    printf("Total size : %lu\n", sobj.st_size);
    printf("Inode number : %lu\n", sobj.st_ino);
    printf("Hardlink count : %lu\n", sobj.st_nlink);
    printf("Owner UID : %u\n", sobj.st_uid);
    printf("Owner GID: %u\n", sobj.st_gid);
    printf("File type and mode : %u\n", sobj.st_mode);
    printf("Last Access/ modify time : %lu\t%lu\n", sobj.st_atime, sobj.st_mtime);

    return 0;
}