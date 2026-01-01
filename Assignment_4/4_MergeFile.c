/*
    * File Merge Utility
    Problem Statement :
        Merge multiplefile into a single output file

    Input:
        output_file, file1, file2, file3...

    Output:
        Combined file content in order
*/

#include<stdio.h>   // Standard I/O functions like printf()
#include<fcntl.h>   // File control options: open(), O_RDONLY, O_WRONLY
#include<errno.h>   // For errno variable and error codes
#include<unistd.h>  // Provides POSIX system calls: read(), write(), close()

#define BUFFER_NO 100

/*
  Function Name : FileMerge
  Description   : take coomand-line input as output and next all as input and write all input file content into output file  
  Input         : int argc - count of command line input
                   char * argv - string  
  Output        : Write data from multiple file into single output file
*/
int FileMerge(int argc, char * argv[])
{
    int fd_input; 
    int fd_out;
    char Buffer[BUFFER_NO];
    int iRet;

    fd_out = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
    if (fd_out == -1)
    {
        perror("Output file");
        return -1;
    }

    for (int i = 2; i < argc; i++)
    {
        fd_input = open(argv[i], O_RDONLY);
        if (fd_input == -1)
        {
            perror(argv[i]);
            continue;
        }

        while ((iRet = read(fd_input, Buffer, sizeof(Buffer))) > 0)
        {
            write(fd_out, Buffer, iRet);
        }

        close(fd_input);
    }

    close(fd_out);
}

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        printf("Usage: %s output_file input1 input2 ...\n", argv[0]);
        return -1;
    }

    FileMerge(argc, argv);

    return 0;
}
