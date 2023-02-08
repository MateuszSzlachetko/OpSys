#include <stdio.h>
#include <time.h>

/*
 * Program po dodaniu opóźnienia nie wyświetlał się na górze top
 * żeby zmienić częstotliwość odświeżania komendy top, należy
 * wywołać ją z flagą top -d seconds, gdzie seconds to zmienna
 * np 0.01 s
 */

int main()
{
    int i = 0;

    struct timespec time;

    time.tv_sec = 0;
    time.tv_nsec = 10000000; // 10ms

    while (1)
    {
        i++;
        nanosleep(&time, &time);
    }
}