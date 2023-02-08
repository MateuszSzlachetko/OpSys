#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        return -1;
    }

    int pipe_fd[2];
    int c;
    FILE *file;

    pipe(pipe_fd);

    if (fork() == 0)
    {
        // child
        close(pipe_fd[1]);
        close(0);        // zamykamy stdin
        dup(pipe_fd[0]); // ma wolne 0 więc dołącza
        execl("/usr/bin/display", "display", (char *)NULL);
        read(pipe_fd[0], &c, 1);
        exit(1);
    }
    // parent
    close(pipe_fd[0]);
    file = fopen(argv[1], "r");
    if (file == NULL)
        printf("File error\n");
    while (!feof(file))
    {
        c = getc(file);
        write(pipe_fd[1], &c, 1);
    }
    // close(pipe_fd[1]);
}