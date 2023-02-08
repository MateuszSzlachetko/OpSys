#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>
#include <unistd.h>

void sigalrmHandler()
{
    printf("SIGALRM catched, exiting\n"); // b)
    exit(1);
}

void sigusr1Handler()
{
    printf("SIGUSR1 catched\n"); // c)
}

void sigusr2Handler()
{
    printf("SIGUSR2 catched\n"); // d)

    // printf("Unlocked\n");
}

void sigtermHandler()
{
    // a)
}

int main()
{
    int i = 0;

    struct timespec time;

    time.tv_sec = 1;
    time.tv_nsec = 10000000; // 10ms

    signal(SIGALRM, sigalrmHandler);
    signal(SIGUSR1, sigusr1Handler);
    signal(SIGTERM, SIG_IGN);

    sigset_t set, oset;

    sigemptyset(&set);
    sigaddset(&set, SIGUSR2);
    sigprocmask(SIG_BLOCK, &set, &oset);

    signal(SIGUSR2, sigusr2Handler);

    while (1)
    {
        i++;

        nanosleep(&time, &time);
        printf("\n %d", i);
        if (!(i % 10))
        {
            sigprocmask(SIG_UNBLOCK, &set, &oset);
            sigprocmask(SIG_BLOCK, &set, &oset);
        }
    }
}