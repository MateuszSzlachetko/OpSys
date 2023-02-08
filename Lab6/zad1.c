#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#define MAX 16

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        return -1;
    }

    char buf[MAX];

    int fd[2], count;
    pid_t p;

    if (pipe(fd) == -1)
    {
        fprintf(stderr, "Pipe Failed");
        return 1;
    }

    p = fork();

    if (p < 0)
    {
        fprintf(stderr, "fork Failed");
        return 1;
    } // Parent process
    else if (p > 0)
    {
        FILE *file;

        file = fopen(argv[1], "r");

        if (NULL == file)
        {
            printf("file can't be opened \n");
        }

        close(fd[0]); // Zamknięcie końca czytającego

        while (fgets(buf, MAX, file) != NULL)
        {
            write(fd[1], buf, strlen(buf) + 1);
        }

        close(fd[1]); // Zamknięcie końca piszącego

        wait(NULL);
    } // child process
    else
    {
        close(fd[1]); // Zamknięcie końca piszącego

        while ((count = read(fd[0], buf, MAX)) > 0)
        {
            write(1, "#", sizeof("#"));
            write(1, buf, count);
            write(1, "# ", sizeof("# "));
        }

        // Zamknięcie końca czytającego
        close(fd[0]);

        exit(0);
    }
}