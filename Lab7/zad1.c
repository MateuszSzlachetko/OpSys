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
    int mem = open("memory", O_RDWR);
    if (fd < 0)
    {
        printf("\n\"%s \" could not open\n",
               "memory");
        exit(1);
    }

    struct stat statbuf;
    int err = fstat(mem, &statbuf);
    if (err < 0)
    {
        printf("\n\"%s \" could not open\n",
               "memory");
        exit(2);
    }

    char *ptr = mmap(NULL, statbuf.st_size,
                     PROT_READ | PROT_WRITE,
                     MAP_SHARED,
                     mem, 0);
    close(fd);
    // plik zmapowany
    struct stat statbuf2;
    char buf[128];
    ssize_t n;
    char *ptr2 = mmap(NULL, statbuf2.st_size,
                      PROT_READ | PROT_WRITE,
                      MAP_SHARED,
                      mem, 0);
    ;
    while (1)
    { //  ptwrzyć plik jako FILE *
        // rzepisać go do pamięci wcześniej ją zwalniając
        printf("Podaj nazwę plik\n");
        scanf("%s", buf);

        fd = open(buf, O_RDWR);
        if (fd < 0)
        {
            printf("\n\"%s \" could not open\n",
                   "memory");
            exit(1);
        }

        err = fstat(fd, &statbuf2);
        if (err < 0)
        {
            printf("\n\"%s \" could not open\n",
                   "memory");
            exit(2);
        }

        err = munmap(ptr2, statbuf.st_size);
        err = munmap(ptr, statbuf.st_size);

        // /ftruncate()

        ptr2 = mmap(NULL, statbuf2.st_size,
                    PROT_READ | PROT_WRITE,
                    MAP_SHARED,
                    fd, 0);
        ptr = mmap(NULL, statbuf2.st_size,
                   PROT_READ | PROT_WRITE,
                   MAP_SHARED,
                   mem, 0);

        statbuf = statbuf2;
        n = write(mem, ptr2, statbuf2.st_size);
    }

    // ssize_t n = write(1, ptr, statbuf.st_size);
    // if (n != statbuf.st_size)
    // {
    //     printf("Write failed\n");
    // }

    // n = write(1, ptr, statbuf.st_size);
    // if (n != statbuf.st_size)
    // {
    //     printf("Write failed\n");
    // }

    // int fd, ret;
    // size_t len_file, len;
    // struct stat st;
    // char *addr;
    // char buf[MAX];

    // if (argc < 2)
    // {
    //     printf("Usage a.out <filename>\n");
    //     return EXIT_FAILURE;
    // }

    // if ((fd = open(argv[1], O_RDWR | O_CREAT, FILEMODE)) < 0)
    // {
    //     perror("Error in file opening");
    //     return EXIT_FAILURE;
    // }

    // if ((ret = fstat(fd, &st)) < 0)
    // {
    //     perror("Error in fstat");
    //     return EXIT_FAILURE;
    // }

    // len_file = st.st_size;

    // /*len_file having the total length of the file(fd).*/

    // if ((addr = mmap(NULL, len_file, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0)) == MAP_FAILED)
    // {
    //     perror("Error in mmap");
    //     return EXIT_FAILURE;
    // }

    // while ((fgets(buf, MAX, stdin)) != NULL)
    // {
    //     len = len_file;
    //     len_file += strlen(buf);
    //     if (ftruncate(fd, len_file) != 0)
    //     {
    //         perror("Error extending file");
    //         return EXIT_FAILURE;
    //     }
    //     if ((addr = mremap(addr, len, len_file, MREMAP_MAYMOVE)) == MAP_FAILED)
    //     {
    //         perror("Error extending mapping");
    //         return EXIT_FAILURE;
    //     }
    //     memcpy(addr + len, buf, len_file - len);
    //     printf("Val:%s\n", addr); // Checking purpose
    // }
    // if ((msync(addr, len, MS_SYNC)) < 0)
    //     perror("Error in msync");

    // if (munmap(addr, len) == -1)
    //     perror("Error in munmap");

    // if (close(fd))
    //     perror("Error in close");

    // return 0;
}
