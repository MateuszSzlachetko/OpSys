#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void *myThreadFun(void *vargp)
{
    int *myid = (int *)vargp;

    printf("Hello SCR. Written by thread %ld\n", vargp);
    pthread_exit(NULL);
}
// Wątki nie wykonywały się kolejno od 0-9 tylko w losowej kolejności
int main()
{
    long i;
    pthread_t tid[10];

    for (i = 0; i < 10; i++)
    {
        pthread_create(&tid[i], NULL, myThreadFun, (void *)i);
    }
    pthread_exit(NULL);
    return 0;
}