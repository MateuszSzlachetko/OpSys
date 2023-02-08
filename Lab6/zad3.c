#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#define FIFO "FIFO"
#define MAX 64

int main(int argc, char *argv[])
{
    // if (argc < 2)
    // {
    //     return -1;
    // }
    int potok_fd;
    potok_fd = open(FIFO, O_WRONLY);
    char buf[MAX];

    FILE *file;

    int i = 1;

    file = fopen(argv[1], "r");

    if (NULL == file)
    {
        printf("file can't be opened \n");
    }

    while (i < argc)
    {
        file = fopen(argv[i], "r");

        while (fgets(buf, MAX, file) != NULL)
        {
            write(potok_fd, buf, strlen(buf) + 1);
            write(potok_fd, "\n", sizeof("\n"));
            sleep(1);
            // rewind(file);
        } // dopisać różne pliki

        fclose(file);
        i++;
    }
}