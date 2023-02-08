#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#define FILEMODE S_IRWXU | S_IRGRP | S_IROTH
#define MAX 150

int main(int argc, char *argv[])
{

    int fd = open("memory", O_RDWR);
    struct stat file_info;
    fstat(fd, &file_info);

    char *memory = mmap(NULL, file_info.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    struct stat new_file_info;
    char buf[128];

    int fd_newfile;
    FILE *fp;
    char c;

    if (fork() == 0)
    {
        execl("/usr/bin/display", "display", "-update", "1", "memory", (char *)NULL);
    }
    // parent
    while (1)
    {
        printf("Podaj nazwę plik\n");
        scanf("%s", buf);

        fd_newfile = open(buf, O_RDWR);

        fstat(fd_newfile, &new_file_info);

        munmap(memory, file_info.st_size);
        ftruncate(fd, new_file_info.st_size);
        memory = mmap(NULL, new_file_info.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

        fp = fopen(buf, "r");

        for (int i = 0; i < new_file_info.st_size; i++)
        {
            memory[i] = fgetc(fp);
        }

        file_info = new_file_info;
        fclose(fp);
        close(fd_newfile);
    }

    close(fd);
}