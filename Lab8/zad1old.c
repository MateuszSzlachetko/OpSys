#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

// The function to be executed by all threads
void *myThreadFun(void *vargp)
{
    // Store the value argument passed to this thread
    int *myid = (int *)vargp;

    printf("Hello SCR. Written by thread %d\n", myid);
    pthread_exit(NULL);
}

int main()
{
    int i;
    pthread_t tid[5];
    void *retvals[5];

    // Let us create three threads
    for (i = 0; i < 4; i++)
    {
        pthread_create(&tid[i], NULL, myThreadFun, (void *)&tid[i]);
        // pthread_join(tid[i], &retvals[i]);
        // pthread_create(&tid[i], NULL, myThreadFun, (void *)&tid[i]);
    }
    pthread_exit(NULL);
    return 0;
}